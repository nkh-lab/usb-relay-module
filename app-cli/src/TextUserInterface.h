#pragma once

namespace nlab {

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

} // namespace nlab