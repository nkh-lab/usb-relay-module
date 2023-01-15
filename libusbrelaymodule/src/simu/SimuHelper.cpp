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

#include "SimuHelper.h"

#include "Utils.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {
namespace simu {

Json::Value BuildJsonTemplate()
{
    constexpr unsigned int kJsonTemplateModuleSize = 2;
    constexpr unsigned int kJsonTemplateChannelSize = 2;
    constexpr char kJsonTemplateModuleName[] = "R%d";

    Json::Value jroot;

    for (unsigned int m_idx = 0; m_idx < kJsonTemplateModuleSize; ++m_idx)
    {
        Json::Value module;
        module[kJsonKeyModuleName] = utils::Sprintf(kJsonTemplateModuleName, m_idx + 1);

        for (unsigned int c_idx = 0; c_idx < kJsonTemplateChannelSize; ++c_idx)
        {
            Json::Value channel;

            channel[kJsonKeyChannelIndex] = c_idx + 1;
            channel[kJsonKeyChannelState] = 0;

            module[kJsonKeyChannels][c_idx] = channel;
        }

        jroot[kJsonKeyModules][m_idx] = module;
    }

    return jroot;
}

bool GetModuleInRootJson(
    const std::string& requested_module,
    Json::Value& jroot,
    Json::Value& jmodule,
    unsigned int& jmodule_idx)
{
    bool ret = false;

    unsigned int jmodule_size = jroot[simu::kJsonKeyModules].size();

    for (unsigned int i = 0; i < jmodule_size; ++i)
    {
        Json::Value& jm = jroot[simu::kJsonKeyModules][i];

        if (jm[simu::kJsonKeyModuleName].asString() == requested_module)
        {
            jmodule = jm;
            jmodule_idx = i;

            ret = true;
            break;
        }
    }

    return ret;
}

bool GetChannelInModuleJson(unsigned int requested_channel, Json::Value& jmodule, Json::Value& jchannel, unsigned int& jchannel_idx)
{
    bool ret = false;

    unsigned int jchannels_size = jmodule[simu::kJsonKeyChannels].size();

    for (unsigned int i = 0; i < jchannels_size; ++i)
    {
        Json::Value& jc = jmodule[simu::kJsonKeyChannels][i];

        if (jc[simu::kJsonKeyChannelIndex].asUInt() == requested_channel)
        {
            jchannel = jc;
            jchannel_idx = i;

            ret = true;
            break;
        }
    }

    return ret;
}

} // namespace simu
} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab