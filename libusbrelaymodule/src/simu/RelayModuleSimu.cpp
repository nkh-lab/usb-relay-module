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

#include "RelayModuleSimu.h"

#include <json/json.h>

#include "SimuHelper.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

RelayModuleSimu::RelayModuleSimu(
    std::shared_ptr<SynchronizedString> simu_file,
    const std::string& info,
    const std::string& name)
    : simu_file_{simu_file}
    , info_{info}
    , name_{name}
{
}

std::string RelayModuleSimu::GetInfo()
{
    return info_;
}

bool RelayModuleSimu::GetNameAndChannels(std::string& module_name, std::vector<bool>& channels)
{
    bool ret = false;

    simu_file_->GetLock();
    std::string file_path = simu_file_->GetResource();
    std::fstream file(file_path, std::ios::in);
    Json::Value jroot, jmodule;
    unsigned int jmodule_idx;
    file >> jroot;

    if (simu::GetModuleInRootJson(name_, jroot, jmodule, jmodule_idx))
    {
        module_name = jmodule[simu::kJsonKeyModuleName].asString();
        auto channels_size = jmodule[simu::kJsonKeyChannels].size();

        for (unsigned int i = 0; i < channels_size; ++i)
        {
            channels.emplace_back(
                jmodule[simu::kJsonKeyChannels][i][simu::kJsonKeyChannelState].asBool());
        }

        ret = true;
    }

    return ret;
}

bool RelayModuleSimu::SetName(const std::string& name)
{
    bool ret = false;

    simu_file_->GetLock();
    std::string file_path = simu_file_->GetResource();
    std::fstream file(file_path, std::ios::in);
    Json::Value jroot, jmodule;
    unsigned int jmodule_idx;
    file >> jroot;

    if (simu::GetModuleInRootJson(name_, jroot, jmodule, jmodule_idx))
    {
        jmodule[simu::kJsonKeyModuleName] = name;
        jroot[simu::kJsonKeyModules][jmodule_idx] = jmodule;

        name_ = name;

        file.close();
        file.open(file_path, std::ios::out | std::ios::trunc);
        file << jroot;

        ret = true;
    }

    return ret;
}

bool RelayModuleSimu::SetChannel(size_t channel, bool state)
{
    bool ret = false;

    simu_file_->GetLock();
    std::string file_path = simu_file_->GetResource();
    std::fstream file(file_path, std::ios::in);
    Json::Value jroot, jmodule, jchannel;
    unsigned int jmodule_idx, jchannel_idx;
    file >> jroot;

    if (simu::GetModuleInRootJson(name_, jroot, jmodule, jmodule_idx))
    {
        if (simu::GetChannelInModuleJson(
                static_cast<unsigned int>(channel), jmodule, jchannel, jchannel_idx))
        {
            jchannel[simu::kJsonKeyChannelState] = state == true ? 1 : 0;
            jroot[simu::kJsonKeyModules][jmodule_idx][simu::kJsonKeyChannels][jchannel_idx] = jchannel;

            file.close();
            file.open(file_path, std::ios::out | std::ios::trunc);
            file << jroot;

            ret = true;
        }
    }

    return ret;
}

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab