#pragma once

#include <gmock/gmock.h>

#include "IRelayModule.h"

namespace nlab {

class MockRelayModule : public IRelayModule
{
public:
    MOCK_METHOD0(GetInfo, std::string());
    MOCK_METHOD2(GetNameAndChannels, bool(std::string& module_name, std::vector<bool>& channels));
    MOCK_METHOD1(SetName, bool(const std::string& name));
    MOCK_METHOD2(SetChannel, bool(size_t channel, bool state));
};

} // namespace nlab