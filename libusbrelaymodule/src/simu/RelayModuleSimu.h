/*
 * Copyright (C) 2023 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#pragma once

#include <memory>

#include <json/json.h>

#include "IRelayModule.h"
#include "SynchronizedResource.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

class RelayModuleSimu final : public IRelayModule
{
public:
    RelayModuleSimu(
        std::shared_ptr<SynchronizedString> simu_file,
        const std::string& info,
        const std::string& name);
    ~RelayModuleSimu() = default;

    std::string GetInfo() override;
    bool GetNameAndChannels(std::string& module_name, std::vector<bool>& channels) override;
    bool SetName(const std::string& name) override;
    bool SetChannel(size_t channel, bool state) override;

private:
    std::shared_ptr<SynchronizedString> simu_file_;
    const std::string info_;
    std::string name_;
};

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab