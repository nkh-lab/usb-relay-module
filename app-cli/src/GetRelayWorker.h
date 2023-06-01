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

#include <string>
#include <vector>

#include "RelayManager.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appcli {

class GetRelayWorker
{
public:
    explicit GetRelayWorker(IRelayManagerPtr relay_manager);
    ~GetRelayWorker() = default;

    bool Run(int argc, char const** argv, std::string& out);

private:
    std::string DoVersionText();
    std::string DoHelpText();
    std::string DoWrongArgumentUsageText();
    std::string DoBadArgumentText(const std::string& bad_arg);

    bool GetState(const std::string& module, int channel, std::string& out);
    bool GetStatesAllModules(const IRelayModulePtrs& modules, std::string& out);
    bool GetStatesRequestedModule(
        const IRelayModulePtrs& modules,
        const std::string& module,
        std::string& out);
    bool GetStateRequestedChannel(
        const IRelayModulePtrs& modules,
        const std::string& module,
        size_t channel,
        std::string& out);

    IRelayManagerPtr relay_manager_;
};

} // namespace appcli
} // namespace usbrelaymodule
} // namespace nkhlab