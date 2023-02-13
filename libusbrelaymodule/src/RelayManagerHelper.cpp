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
#include "Utils.h"

namespace nkhlab {
namespace usbrelaymodule {

RelayManagerHelper::SetChannelResult RelayManagerHelper::SetChannel(IRelayManager* relay_manager, const std::string& channel, bool state)
{
    SetChannelResult ret = SetChannelResult::kNoRequestedModule;
    std::string req_module;
    size_t req_channel;

    utils::SplitModuleChannelStr(channel, req_module, req_channel);

    auto modules = relay_manager->GetModules();

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        if (module_name == req_module)
        {
            if (req_channel > 0 && req_channel <= channels.size())
            {
                if (!m->SetChannel(req_channel, state))
                    ret = SetChannelResult::kSetChannelError;
            }
            else ret = SetChannelResult::kNoRequestedChannel;
            break;
        }
    }

    return ret;
}

} // namespace usbrelaymodule
} // namespace nkhlab

#undef DLL_EXPORT