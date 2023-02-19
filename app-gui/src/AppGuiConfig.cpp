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

#include "AppGuiConfig.h"

#include <json/json.h>

#include "FileHelper.h"
#include "StringHelper.h"
#include "nkh-lab/logger.hpp"

using namespace nkhlab::usbrelaymodule::utils;

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

AppGuiConfig::AppGuiConfig(const std::string& config_file)
    : config_file_{config_file}
    , start_app_pos_{wxDefaultPosition}
    , start_app_size_{wxDefaultSize}
    , is_hide_all_channels_page_{false}
{
    LOG_FNC;
    ReadConfigFromFile();
}

AppGuiConfig::~AppGuiConfig()
{
    LOG_FNC;
    WriteConfigToFile();
}

const wxSize& AppGuiConfig::GetStartAppSize()
{
    return start_app_size_;
}

const wxPoint& AppGuiConfig::GetStartAppPosition()
{
    return start_app_pos_;
}

void AppGuiConfig::SetStartAppSize(const wxSize& size)
{
    LOG_DBG << StringHelper::Sprintf("w: %d, h: %d", size.GetWidth(), size.GetHeight());

    start_app_size_ = size;
}

void AppGuiConfig::SetStartAppPosition(const wxPoint& pos)
{
    LOG_DBG << StringHelper::Sprintf("x: %d, y: %d", pos.x, pos.y);

    start_app_pos_ = pos;
}

bool AppGuiConfig::IsHideAllChannelsPage()
{
    return is_hide_all_channels_page_;
}

std::vector<AliasPage> AppGuiConfig::GetAliasPages()
{
    return {};
}

void AppGuiConfig::WriteConfigToFile()
{
    Json::Value jroot;

    jroot["appStartSize"] = 123;

    FileHelper::WriteFile(config_file_, Json::StyledWriter().write(jroot));
}

void AppGuiConfig::ReadConfigFromFile()
{
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab