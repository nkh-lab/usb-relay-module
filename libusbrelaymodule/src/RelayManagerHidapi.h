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

#include <iostream>

#include "hidapi.h"

#include "HidapiUtils.h"
#include "IRelayManager.h"
#include "RelayModuleDcttech.h"
#include "cpp-utils/StringHelper.h"

using namespace nkhlab::cpputils;

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

template <typename TRelayModule>
class RelayManagerHidapi final : public IRelayManager
{
public:
    RelayManagerHidapi() = default;
    ~RelayManagerHidapi() = default;

    IRelayModulePtrs GetModules() override
    {
        std::list<IRelayModulePtr> modules;

        hid_device_info* dev =
            hid_enumerate(TRelayModule::GetVendorId(), TRelayModule::GetProductId());
        hid_device_info* next = dev;

        while (next)
        {
            size_t channels_size = 0;
            if (next->product_string)
                static_cast<size_t>(atoi(&StringHelper::WstrToStr(next->product_string).back()));

            modules.emplace_back(std::make_shared<RelayModuleDcttech>(
                HidDeviceInfoToStr(next), next->path, channels_size));

            next = next->next;
        }
        hid_free_enumeration(dev);

        return modules;
    }
};

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab
