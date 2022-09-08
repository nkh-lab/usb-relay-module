#pragma once

#include <iostream>

#include "hidapi.h"

#include "HidapiUtils.h"
#include "IRelayManager.h"
#include "RelayModuleDcttech.h"
#include "Utils.h"

namespace nlab {

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
            size_t channels_size =
                static_cast<size_t>(atoi(&utils::PwstrToStr(next->product_string).back()));

            modules.emplace_back(std::make_shared<RelayModuleDcttech>(
                HidDeviceInfoToStr(next), next->path, channels_size));

            next = next->next;
        }
        hid_free_enumeration(dev);

        return modules;
    }
};

} // namespace nlab
