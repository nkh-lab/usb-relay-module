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

#include "SetRelayWorker.h"

#include "Config.h"
#include "LightArgParser.h"
#include "RelayManagerHelper.h"
#include "TextUserInterface.h"
#include "cpp-utils/StringHelper.h"

using namespace nkhlab::lightargparser;
using namespace nkhlab::cpputils;
using namespace nkhlab::usbrelaymodule::config;

namespace nkhlab {
namespace usbrelaymodule {
namespace appcli {

SetRelayWorker::SetRelayWorker(IRelayManagerPtr relay_manager)
    : relay_manager_{std::move(relay_manager)}
{
}

bool SetRelayWorker::Run(int argc, char const** argv, std::string& out)
{
    bool ret = true;
    out.clear();

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
        else if (conf_args.size() == 0 && data_args.size() == 1)
        {
            std::string req_module{};
            size_t req_channel = 0; // 0 = no, begins from 1, eg REL_1=1

            RelayManagerHelper::SplitChannelName(data_args.begin()->first, req_module, req_channel);

            if (req_channel == 0 && !data_args.begin()->second.empty() &&
                data_args.begin()->second[0] != '1' && data_args.begin()->second[0] != '0')
            {
                std::string new_name{data_args.begin()->second};
                ret = RenameModule(req_module, new_name, out);
            }
            else if (req_channel > 0 && (data_args.begin()->second[0] == '1' || data_args.begin()->second[0] == '0'))
            {
                bool state = data_args.begin()->second[0] == '1' ? true : false;
                ret = SetChannel(req_module, req_channel, state, out);
            }
        }

        if (!ret && out.empty()) out = DoWrongArgumentUsageText();
    }
    else
    {
        out = DoBadArgumentText(bad_arg);
    }

    return ret;
}

std::string SetRelayWorker::DoVersionText()
{
    return StringHelper::Sprintf(
        TextUserInterface::kVersion,
        config::kProjectVerMajor,
        config::kProjectVerMinor,
        config::kProjectVerPatch,
        config::kGitCommitHash);
}

std::string SetRelayWorker::DoHelpText()
{
    return TextUserInterface::kSetRelayHelp;
}

std::string SetRelayWorker::DoWrongArgumentUsageText()
{
    return TextUserInterface::kErrorWrongArgumentUsage;
}

std::string SetRelayWorker::DoBadArgumentText(const std::string& bad_arg)
{
    return StringHelper::Sprintf(TextUserInterface::kErrorBadArgument, bad_arg.c_str());
}

bool SetRelayWorker::RenameModule(const std::string& module, const std::string& new_module, std::string& out)
{
    bool ret = false;

    out = StringHelper::Sprintf(TextUserInterface::kErrorNoRequestedModule, module.c_str());

    auto modules = relay_manager_->GetModules();

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == module || module.empty())
        {
            ret = m->SetName(new_module);
            out.clear();
            break;
        }
    }

    return ret;
}

bool SetRelayWorker::SetChannel(const std::string& module, size_t channel, bool state, std::string& out)
{
    bool ret = false;

    out = StringHelper::Sprintf(TextUserInterface::kErrorNoRequestedModule, module.c_str());

    auto modules = relay_manager_->GetModules();

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == module)
        {
            if (channel <= channels.size())
            {
                ret = m->SetChannel(channel - 1, state);
                out.clear();
            }
            else
            {
                ret = false;
                out = StringHelper::Sprintf(
                    TextUserInterface::kErrorNoRequestedChannel, channel, module.c_str());
            }
        }
    }

    return ret;
}

} // namespace appcli
} // namespace usbrelaymodule
} // namespace nkhlab
