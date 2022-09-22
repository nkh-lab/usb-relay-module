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

namespace nkhlab {
namespace usbrelaymodule {
namespace appcli {

struct TextUserInterface
{
    static const char* kVersion;
    static const char* kGetRelayHelp;
    static const char* kSetRelayHelp;
    static const char* kErrorWrongArgumentUsage;
    static const char* kErrorBadArgument;
    static const char* kGetChannelState;
    static const char* kGetRelayInfoAndState;
    static const char* kChannelNameAndState;
    static const char* kNoModules;
    static const char* kErrorNoRequestedModule;
    static const char* kErrorNoRequestedChannel;
    static const char* kErrorInaccessible;
};

} // namespace appcli
} // namespace usbrelaymodule
} // namespace nkhlab