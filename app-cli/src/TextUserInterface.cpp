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

#include "TextUserInterface.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appcli {

// clang-format off

const char* TextUserInterface::kVersion = "v%d.%d.%d\n";

const char* TextUserInterface::kGetRelayHelp =
    "Usage:\n"
    "    <ModuleName>_<ChannelNumber>    Return a state 0 or 1 of the requested channel (numbering starts from 1)\n"
    "    <ModuleName>                    Return full information about the requested module\n"
    "    <>                              No arguments provided, return full information about all detected modules\n"
    "\n"
    "Service commands:\n"
    "    -h | --help                     Display this help text\n"
    "    -v | --version                  Display version information\n";

const char* TextUserInterface::kSetRelayHelp =
    "Usage:\n"
    "    <ModuleName>_<ChannelNumber>=<StateToSet>    Set the state 0 or 1 of the specified channel (numbering starts from 1)\n"
    "    <ModuleName>=<NewModuleName>                 Rename module\n"
    "\n"
    "Service commands:\n"
    "    -h | --help                                  Display this help text\n"
    "    -v | --version                               Display version information\n";

const char* TextUserInterface::kGetChannelState =
    "%d\n";

const char* TextUserInterface::kGetRelayInfoAndState =
    "%s"
    "module_name:      %s\n"
    "%s";

const char* TextUserInterface::kChannelNameAndState =
    "channel_%d:        %d\n";

const char* TextUserInterface::kNoModules =
    "No USB relay modules detected\n";

const char* TextUserInterface::kErrorWrongArgumentUsage =
    "ERROR: Wrong argument usage!\n"
    "       Use the '-h | --help' command to see a description of usage.\n";

const char* TextUserInterface::kErrorBadArgument =
    "ERROR: Bad argument '%s' provided!\n";

const char* TextUserInterface::kErrorNoRequestedModule =
    "ERROR: No requested '%s' USB relay module detected!\n";

const char* TextUserInterface::kErrorNoRequestedChannel =
    "ERROR: No requested channel '%d' in '%s' USB relay module!\n";

const char* TextUserInterface::kErrorInaccessible =
    "ERROR: Inaccessible!";

// clang-format on

} // namespace appcli
} // namespace usbrelaymodule
} // namespace nkhlab
