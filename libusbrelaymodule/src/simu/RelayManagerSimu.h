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

#include <fstream>
#include <memory>

#include "IRelayManager.h"
#include "RelayModuleSimu.h"
#include "SimuHelper.h"
#include "SynchronizedResource.h"
#include "Utils.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

#ifdef __linux__
constexpr char kModuleInfo[] =
    "path:             /dev/hidraw%d\n"
    "vendor_id:        0x16c0\n"
    "product_id:       0x05df\n"
    "serial_number:\n"
    "release_number:   256\n"
    "manufacturer:     www.dcttech.com\n"
    "product:          USBRelay%d\n"
    "interface_number: 0\n";
#else
constexpr char kModuleInfo[] =
    "path:             "
    "\\?\hid#vid_16c0&pid_05df#6&5a5089d&0&0000#{4d1e55b2-f16f-11cf-88cb-0011110000%d}\n"
    "vendor_id:        0x16c0\n"
    "product_id:       0x05df\n"
    "serial_number:    (null)\n"
    "release_number:   256\n"
    "manufacturer:     www.dcttech.com\n"
    "product:          USBRelay%d\n"
    "interface_number: -1\n";
#endif

template <typename TRelayModule>
class RelayManagerSimu final : public IRelayManager
{
public:
    RelayManagerSimu()
        : simu_file_{std::make_shared<SynchronizedString>(std::string(simu::kFileName))}
    {
        CreateSimuFileIfNotExist();
    }

    ~RelayManagerSimu() = default;

    IRelayModulePtrs GetModules() override
    {
        std::list<IRelayModulePtr> modules;
        simu_file_->GetLock();
        std::string file_path = simu_file_->GetResource();
        std::fstream file(file_path, std::ios::in);
        Json::Value jroot;
        file >> jroot;

        auto jmodules_size = jroot[simu::kJsonKeyModules].size();

        for (uint i = 0; i < jmodules_size; ++i)
        {
            Json::Value& jmodule = jroot[simu::kJsonKeyModules][i];

            auto jchannels_size = jmodule[simu::kJsonKeyChannels].size();
            auto info = utils::Sprintf(kModuleInfo, i + 1, jchannels_size);

            modules.emplace_back(std::make_shared<RelayModuleSimu>(
                simu_file_, info, jmodule[simu::kJsonKeyModuleName].asString()));
        }

        return modules;
    }

private:
    void CreateSimuFileIfNotExist()
    {
        simu_file_->GetLock();
        std::string file_path = simu_file_->GetResource();

        std::fstream file(file_path, std::ios::in);

        if (!file.good())
        {
            file.close();
            file.open(file_path, std::ios::out);

            file << simu::BuildJsonTemplate();
        }
    }

    std::shared_ptr<SynchronizedString> simu_file_;
};

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab
