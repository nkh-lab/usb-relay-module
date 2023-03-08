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

class SetRelayWorker
{
public:
    explicit SetRelayWorker(IRelayManagerPtr relay_manager);
    ~SetRelayWorker() = default;

    bool Run(int argc, char const** argv, std::string& out);

private:
    std::string DoVersionText();
    std::string DoHelpText();
    std::string DoWrongArgumentUsageText();
    std::string DoBadArgumentText(const std::string& bad_arg);

    bool RenameModule(const std::string& module, const std::string& new_module, std::string& out);
    bool SetChannel(const std::string& module, size_t channel, bool state, std::string& out);

    IRelayManagerPtr relay_manager_;
};

} // namespace appcli
} // namespace usbrelaymodule
} // namespace nkhlab
