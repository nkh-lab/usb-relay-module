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