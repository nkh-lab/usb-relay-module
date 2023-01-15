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

#include <json/json.h>

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {
namespace simu {

constexpr char kFileName[] = "usbrelaymodule-simu.json";

constexpr char kJsonKeyModules[] = "modules";
constexpr char kJsonKeyModuleName[] = "name";
constexpr char kJsonKeyChannels[] = "channels";
constexpr char kJsonKeyChannelIndex[] = "index";
constexpr char kJsonKeyChannelState[] = "state";

Json::Value BuildJsonTemplate();

bool GetModuleInRootJson(
    const std::string& requested_module,
    Json::Value& jroot,
    Json::Value& jmodule,
    unsigned int& jmodule_idx);
bool GetChannelInModuleJson(
    unsigned int requested_channel,
    Json::Value& jmodule,
    Json::Value& jchannel,
    unsigned int& jchannel_idx);

} // namespace simu
} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab