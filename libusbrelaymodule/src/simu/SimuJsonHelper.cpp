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

#include "SimuJsonHelper.h"

#include "cpp-utils/StringHelper.h"

using namespace nkhlab::cpputils;

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {
namespace simu {

Json::Value SimuJsonHelper::BuildJsonTemplate()
{
    Json::Value jroot;

    for (unsigned int m_idx = 0; m_idx < kJsonTemplateModuleSize; ++m_idx)
    {
        std::string module = StringHelper::Sprintf(kJsonTemplateModuleName, m_idx + 1);

        for (unsigned int c_idx = 0; c_idx < kJsonTemplateChannelSize; ++c_idx)
        {
            jroot[module].append(0);
        }
    }

    return jroot;
}

std::map<std::string, std::vector<bool>> SimuJsonHelper::JsonToModules(const Json::Value& jroot)
{
    std::map<std::string, std::vector<bool>> modules;

    for (const std::string& m : jroot.getMemberNames())
    {
        const Json::Value& jm = jroot[m];
        std::vector<bool> channels;

        for (const auto& jc : jm)
        {
            try
            {
                channels.emplace_back(jc.asBool());
            }
            catch (...)
            {
            }
        }

        modules.emplace(m, channels);
    }

    return modules;
}

bool SimuJsonHelper::ChangeModuleNameInJson(
    Json::Value& jroot,
    const std::string& old_module_name,
    const std::string& new_module_name)
{
    bool ret = false;

    if (jroot.isMember(old_module_name))
    {
        const Json::Value v = jroot[old_module_name];

        jroot.removeMember(old_module_name);
        jroot[new_module_name] = v;

        ret = true;
    }

    return ret;
}

bool SimuJsonHelper::SetChannelStateInJson(
    Json::Value& jroot,
    const std::string& module,
    size_t channel,
    bool state)
{
    bool ret = false;

    if (channel > 0 && jroot.isMember(module) && jroot[module].size() > channel - 1)
    {
        jroot[module][static_cast<int>(channel - 1)] = static_cast<int>(state);

        ret = true;
    }

    return ret;
}

} // namespace simu
} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab