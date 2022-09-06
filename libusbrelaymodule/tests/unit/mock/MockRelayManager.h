#pragma once

#include <gmock/gmock.h>

#include "IRelayManager.h"

namespace nlab {

class MockRelayManager : public IRelayManager
{
public:
    MOCK_METHOD0(GetModules, IRelayModulePtrs());
};

} // namespace nlab
