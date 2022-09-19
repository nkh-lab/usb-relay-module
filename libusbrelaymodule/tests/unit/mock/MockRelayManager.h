#pragma once

#include <gmock/gmock.h>

#include "IRelayManager.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace tests {

class MockRelayManager : public IRelayManager
{
public:
    MOCK_METHOD0(GetModules, IRelayModulePtrs());
};

} // namespace tests
} // namespace usbrelaymodule
} // namespace nkhlab
