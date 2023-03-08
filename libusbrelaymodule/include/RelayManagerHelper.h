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

#pragma once

#include <list>
#include <memory>

#include "IRelayManager.h"

#ifdef __linux__
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

//
// About the naming used:
//
// channel_name = <module>_<channel>, channel begins from 1
// channel_idx  = channel - 1, begins from 0
//
// Example: channel_name = "R2_1" --> module = "R2", channel = 1, channel_idx = 0
//

namespace nkhlab {
namespace usbrelaymodule {

class DLL_EXPORT RelayManagerHelper
{
public:
    RelayManagerHelper() = delete;

    enum class SetChannelResult
    {
        kOk,
        kNoRequestedModule,
        kNoRequestedChannel,
        kSetChannelError
    };

    //
    // channel_name - <module>_<channel(from 1)>, e.g. "R2_1"
    //
    static SetChannelResult SetChannel(
        IRelayManager* relay_manager,
        const std::string& channel_name,
        bool state);

    //
    // channel_name - <module>_<channel(from 1)>, e.g. "R2_1"
    //
    static void SplitChannelName(const std::string& channel_name, std::string& module, size_t& channel);
};

} // namespace usbrelaymodule
} // namespace nkhlab

#undef DLL_EXPORT
