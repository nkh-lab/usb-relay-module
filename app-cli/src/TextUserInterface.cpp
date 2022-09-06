#include "TextUserInterface.h"

namespace nlab {

// clang-format off

const char* TextUserInterface::kVersion = "v%d.%d.%d\n";

const char* TextUserInterface::kHelp =
    "Usage:\n"
    "    <ModuleName>_<ChannelNumber>    Return a state 0 or 1 of the requested channel 1..8\n"
    "    <ModuleName>                    Return full information about the requested module\n"
    "    <>                              No arguments provided, return full information about all detected modules\n"
    "\n"
    "Service commands:\n"
    "    -h | --help                     Display this help text\n"
    "    -v | --version                  Display version information\n";

const char* TextUserInterface::kWrongArgumentUsage =
    "Wrong argument usage!\n"
    "Use the '-h | --help' command to see a description of usage.\n";

const char* TextUserInterface::kBadArgument =
    "Bad argument '%s' provided!\n";

const char* TextUserInterface::kGetChannelState =
    "%d\n";

const char* TextUserInterface::kGetRelayInfoAndState =
    "%s\n"
    "module_name:      %s\n"
    "%s\n";

const char* TextUserInterface::kChannelNameAndState =
    "channel_%d:        %d\n";

const char* TextUserInterface::kNoUsbRelayModule =
    "No USB relay module detected\n";

// clang-format on

} // namespace nlab