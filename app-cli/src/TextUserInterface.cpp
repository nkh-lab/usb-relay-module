#include "TextUserInterface.h"

namespace nlab {

const char* TextUserInterface::kVersion = "v%d.%d.%d\n";
const char* TextUserInterface::kHelp = "This is help text!\n";
const char* TextUserInterface::kWrongArgumentUsage = "This is wrong argument usage text!\n";
const char* TextUserInterface::kBadArgument = "This is bad argument %s text!\n";

const char* TextUserInterface::kGetChannelState = "%d\n";
const char* TextUserInterface::kGetRelayInfoAndState = "%s\n";

const char* TextUserInterface::kNoUsbRelayModule = "No USB relay module detected\n";

} // namespace nlab