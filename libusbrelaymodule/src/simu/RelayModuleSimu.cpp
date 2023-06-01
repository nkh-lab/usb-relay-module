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

#include "SimuJsonHelper.h"
#include "cpp-utils/FileHelper.h"

using namespace nkhlab::cpputils;

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
    Json::Reader jreader;
    Json::Value jroot;

    bool parsed = jreader.parse(FileHelper::ReadFile(file_path).str(), jroot);

    if (parsed)
    {
        auto parsed_modules = simu::SimuJsonHelper::JsonToModules(jroot);

        if (parsed_modules.count(name_))
        {
            module_name = name_;
            channels = parsed_modules[name_];

            ret = true;
        }
    }

    return ret;
}

bool RelayModuleSimu::SetName(const std::string& name)
{
    bool ret = false;

    simu_file_->GetLock();
    std::string file_path = simu_file_->GetResource();
    Json::Reader jreader;
    Json::Value jroot;

    bool parsed = jreader.parse(FileHelper::ReadFile(file_path).str(), jroot);

    if (parsed)
    {
        if (simu::SimuJsonHelper::ChangeModuleNameInJson(jroot, name_, name))
        {
            FileHelper::WriteFile(file_path, Json::StyledWriter().write(jroot));
            name_ = name;
            ret = true;
        }
    }

    return ret;
}

bool RelayModuleSimu::SetChannel(size_t channel_idx, bool state)
{
    bool ret = false;

    simu_file_->GetLock();
    std::string file_path = simu_file_->GetResource();
    Json::Reader jreader;
    Json::Value jroot;

    bool parsed = jreader.parse(FileHelper::ReadFile(file_path).str(), jroot);

    if (parsed)
    {
        if (simu::SimuJsonHelper::SetChannelStateInJson(jroot, name_, channel_idx, state))
        {
            FileHelper::WriteFile(file_path, Json::StyledWriter().write(jroot));
            ret = true;
        }
    }

    return ret;
}

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab
