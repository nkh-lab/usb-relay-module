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

#include <gmock/gmock.h>

#include "IRelayModule.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace tests {

class MockRelayModule : public IRelayModule
{
public:
    MOCK_METHOD0(GetInfo, std::string());
    MOCK_METHOD2(GetNameAndChannels, bool(std::string& module_name, std::vector<bool>& channels));
    MOCK_METHOD1(SetName, bool(const std::string& name));
    MOCK_METHOD2(SetChannel, bool(size_t channel, bool state));
};

} // namespace tests
} // namespace usbrelaymodule
} // namespace nkhlab