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

#include <map>
#include <string>
#include <vector>

#include <json/json.h>

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {
namespace simu {

constexpr char kFileName[] = "usbrelaymodule-simu.json";

constexpr unsigned int kJsonTemplateModuleSize = 2;
constexpr unsigned int kJsonTemplateChannelSize = 2;
constexpr char kJsonTemplateModuleName[] = "R%d";

class SimuJsonHelper
{
private:
    SimuJsonHelper();

public:
    static Json::Value BuildJsonTemplate();
    static std::map<std::string, std::vector<bool>> JsonToModules(const Json::Value& jroot);
    static bool ChangeModuleNameInJson(
        Json::Value& jroot,
        const std::string& old_module_name,
        const std::string& new_module_name);
    static bool SetChannelStateInJson(Json::Value& jroot, const std::string& module, size_t channel, bool state);
};

} // namespace simu
} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab