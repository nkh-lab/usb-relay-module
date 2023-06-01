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

#include "RelayManagerHelper.h"

#include "cpp-utils/StringHelper.h"

using namespace nkhlab::cpputils;

namespace nkhlab {
namespace usbrelaymodule {

RelayManagerHelper::SetChannelResult RelayManagerHelper::SetChannel(
    IRelayManager* relay_manager,
    const std::string& channel_name,
    bool state)
{
    SetChannelResult ret = SetChannelResult::kNoRequestedModule;
    std::string req_module;
    int req_channel;

    SplitChannelName(channel_name, req_module, req_channel);

    auto modules = relay_manager->GetModules();

    for (auto m : modules)
    {
        std::string module;
        std::vector<bool> channels;

        m->GetNameAndChannels(module, channels);

        if (module == req_module)
        {
            if (req_channel > 0 && req_channel <= static_cast<int>(channels.size()))
            {
                if (m->SetChannel(req_channel - 1, state))
                    ret = SetChannelResult::kOk;
                else
                    ret = SetChannelResult::kSetChannelError;
            }
            else
                ret = SetChannelResult::kNoRequestedChannel;
            break;
        }
    }

    return ret;
}

void RelayManagerHelper::SplitChannelName(const std::string& channel_name, std::string& module, int& channel)
{
    const char* kModuleChannelDelimiter = "_";

    size_t delimiter_pos = channel_name.find_last_of(kModuleChannelDelimiter);

    if (delimiter_pos != std::string::npos)
    {
        try
        {
            module = channel_name.substr(0, delimiter_pos);
            channel = std::stoi(channel_name.substr(delimiter_pos + 1));
        }
        catch (...)
        {
            module = channel_name;
            channel = -1;
        }
    }
    else
    {
        module = channel_name;
        channel = -1;
    }
}

std::map<std::string, bool> RelayManagerHelper::GetAllChannels(IRelayManager* relay_manager)
{
    std::map<std::string, bool> all_cannels;
    auto modules = relay_manager->GetModules();

    for (const auto& m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        for (size_t c = 0; c < channels.size(); ++c)
        {
            all_cannels.emplace(
                StringHelper::Sprintf("%s_%d", module_name.c_str(), c + 1), channels[c]);
        }
    }

    return all_cannels;
}

} // namespace usbrelaymodule
} // namespace nkhlab

#undef DLL_EXPORT