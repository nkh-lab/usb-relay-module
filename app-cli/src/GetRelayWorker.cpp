/*
 * Copyright (C) 2022 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#include "GetRelayWorker.h"

#include "Config.h"
#include "LightArgParser.h"
#include "TextUserInterface.h"
#include "Utils.h"

using namespace nkhlab::lightargparser;
using namespace nkhlab::usbrelaymodule::utils;
using namespace nkhlab::usbrelaymodule::config;

namespace {
const char* kAllRelays = "";
const size_t kAllChannels = 0;
} // namespace

namespace nkhlab {
namespace usbrelaymodule {
namespace appcli {

GetRelayWorker::GetRelayWorker(std::unique_ptr<IRelayManager> relay_manager)
    : relay_manager_{std::move(relay_manager)}
{
}

bool GetRelayWorker::Run(int argc, char const** argv, std::string& out)
{
    bool ret = true;

    LightArgParser lap(argc, argv);

    Args_t conf_args, data_args;
    std::string bad_arg;

    ret = lap.Parse(conf_args, data_args, bad_arg);

    if (ret)
    {
        ret = false;

        LightArgParserHelper conf_args_h(conf_args);
        LightArgParserHelper data_args_h(data_args);

        if (conf_args.size() == 1 && data_args.size() == 0 &&
            conf_args_h.AnyKeyExists({"h", "help"}))
        {
            out = DoHelpText();
            ret = true;
        }
        else if (
            conf_args.size() == 1 && data_args.size() == 0 &&
            conf_args_h.AnyKeyExists({"v", "version"}))
        {
            out = DoVersionText();
            ret = true;
        }
        else if (conf_args.size() == 0)
        {
            std::string req_relay{kAllRelays};
            size_t req_channel{kAllChannels};

            if (data_args.size() == 0)
            {
                ret = true;
            }
            else if (data_args.size() == 1 && data_args.begin()->second.empty())
            {
                SplitModuleChannelStr(data_args.begin()->first, req_relay, req_channel);
                ret = true;
            }

            if (ret) ret = GetState(req_relay, req_channel, out);
        }

        if (!ret && out.empty()) out = DoWrongArgumentUsageText();
    }
    else
    {
        out = DoBadArgumentText(bad_arg);
    }

    return ret;
}

std::string GetRelayWorker::DoVersionText()
{
    return Sprintf(TextUserInterface::kVersion, kProjectVerMajor, kProjectVerMinor, kProjectVerPatch);
}

std::string GetRelayWorker::DoHelpText()
{
    return TextUserInterface::kGetRelayHelp;
}

std::string GetRelayWorker::DoWrongArgumentUsageText()
{
    return TextUserInterface::kErrorWrongArgumentUsage;
}

std::string GetRelayWorker::DoBadArgumentText(const std::string& bad_arg)
{
    return Sprintf(TextUserInterface::kErrorBadArgument, bad_arg.c_str());
}

bool GetRelayWorker::GetState(const std::string& module, size_t channel, std::string& out)
{
    bool ret = true;
    out = TextUserInterface::kNoModules;
    auto modules = relay_manager_->GetModules();

    if (modules.size() > 0)
    {
        out.clear();

        if (module.empty())
            ret = GetStatesAllModules(modules, out);
        else
        {
            if (channel == 0)
                ret = GetStatesRequestedModule(modules, module, out);
            else
                ret = GetStateRequestedChannel(modules, module, channel, out);
        }
    }

    return ret;
}

bool GetRelayWorker::GetStatesAllModules(const IRelayModulePtrs& modules, std::string& out)
{
    bool ret = true;

    for (auto m : modules)
    {
        std::string module_name, channels_out;
        std::vector<bool> channels;

        if (m->GetNameAndChannels(module_name, channels))
        {
            for (size_t i = 0; i < channels.size(); ++i)
            {
                channels_out += Sprintf(
                    TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(channels[i]));
            }
        }
        else
        {
            module_name = Sprintf("< %s >", TextUserInterface::kErrorInaccessible);

            if (ret) ret = false;
        }

        out += Sprintf(
            TextUserInterface::kGetRelayInfoAndState,
            m->GetInfo().c_str(),
            module_name.c_str(),
            channels_out.c_str());

        if (m != modules.back()) out += "\n";
    }

    return ret;
}

bool GetRelayWorker::GetStatesRequestedModule(
    const IRelayModulePtrs& modules,
    const std::string& module,
    std::string& out)
{
    bool ret = false;
    out = Sprintf(TextUserInterface::kErrorNoRequestedModule, module.c_str());

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == module)
        {
            std::string channels_out;

            for (size_t i = 0; i < channels.size(); ++i)
            {
                channels_out += Sprintf(
                    TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(channels[i]));
            }

            out = Sprintf(
                TextUserInterface::kGetRelayInfoAndState,
                m->GetInfo().c_str(),
                module_name.c_str(),
                channels_out.c_str());

            ret = true;
        }
    }

    return ret;
}

bool GetRelayWorker::GetStateRequestedChannel(
    const IRelayModulePtrs& modules,
    const std::string& module,
    size_t channel,
    std::string& out)
{
    bool ret = false;
    out = Sprintf(TextUserInterface::kErrorNoRequestedModule, module.c_str());

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == module)
        {
            if (channel <= channels.size())
            {
                out = Sprintf(
                    TextUserInterface::kGetChannelState, static_cast<int>(channels[channel - 1]));
                ret = true;
            }
            else
            {
                out = Sprintf(TextUserInterface::kErrorNoRequestedChannel, channel, module.c_str());
            }
        }
    }

    return ret;
}

} // namespace appcli
} // namespace usbrelaymodule
} // namespace nkhlab
