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

constexpr int kAppMinSizeW = 250;
constexpr int kAppMinSizeH = 300;

constexpr char kJsonKeyX[] = "x";
constexpr char kJsonKeyY[] = "y";
constexpr char kJsonKeyW[] = "w";
constexpr char kJsonKeyH[] = "h";
constexpr char kJsonKeyAppStartPos[] = "appStartPosition";
constexpr char kJsonKeyAppStartSize[] = "appStartSize";
constexpr char kJsonKeyAppMinSize[] = "appMinSize";

AppGuiConfig::AppGuiConfig(const std::string& config_file)
    : config_file_{config_file}
    , app_start_pos_{wxDefaultPosition}
    , app_start_size_{wxDefaultSize}
    , app_min_size_{kAppMinSizeW, kAppMinSizeH}
    , is_hide_all_channels_page_{false}
{
    LOG_FNC;

    if (FileHelper::ExistFile(config_file_)) ReadConfigFromFile();
}

AppGuiConfig::~AppGuiConfig()
{
    LOG_FNC;
    WriteConfigToFile();
}

const wxSize& AppGuiConfig::GetAppStartSize()
{
    return app_start_size_;
}

const wxSize& AppGuiConfig::GetAppMinSize()
{
    return app_min_size_;
}

const wxPoint& AppGuiConfig::GetAppStartPosition()
{
    return app_start_pos_;
}

void AppGuiConfig::SetAppStartSize(const wxSize& size)
{
    LOG_DBG << StringHelper::Sprintf("w: %d, h: %d", size.GetWidth(), size.GetHeight());

    app_start_size_ = size;
}

void AppGuiConfig::SetAppMinSize(const wxSize& size)
{
    LOG_DBG << StringHelper::Sprintf("w: %d, h: %d", size.GetWidth(), size.GetHeight());

    app_min_size_ = size;
}

void AppGuiConfig::SetAppStartPosition(const wxPoint& pos)
{
    LOG_DBG << StringHelper::Sprintf("x: %d, y: %d", pos.x, pos.y);

    app_start_pos_ = pos;
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
    Json::Value jroot, jvalue;

    jvalue[kJsonKeyX] = app_start_pos_.x;
    jvalue[kJsonKeyY] = app_start_pos_.y;

    jroot[kJsonKeyAppStartPos] = jvalue;

    jvalue.clear();

    jvalue[kJsonKeyW] = app_start_size_.GetWidth();
    jvalue[kJsonKeyH] = app_start_size_.GetHeight();

    jroot[kJsonKeyAppStartSize] = jvalue;

    jvalue.clear();

    jvalue[kJsonKeyW] = app_min_size_.GetWidth();
    jvalue[kJsonKeyH] = app_min_size_.GetHeight();

    jroot[kJsonKeyAppMinSize] = jvalue;

    FileHelper::WriteFile(config_file_, Json::StyledWriter().write(jroot));
}

void AppGuiConfig::ReadConfigFromFile()
{
    Json::Value jroot;
    int x, y, w, h;

    FileHelper::ReadFile(config_file_) >> jroot;

    x = jroot[kJsonKeyAppStartPos][kJsonKeyX].asInt();
    y = jroot[kJsonKeyAppStartPos][kJsonKeyY].asInt();

    SetAppStartPosition(wxPoint(x, y));

    w = jroot[kJsonKeyAppStartSize][kJsonKeyW].asInt();
    h = jroot[kJsonKeyAppStartSize][kJsonKeyH].asInt();

    SetAppStartSize(wxSize(w, h));

    w = jroot[kJsonKeyAppMinSize][kJsonKeyW].asInt();
    h = jroot[kJsonKeyAppMinSize][kJsonKeyH].asInt();

    SetAppMinSize(wxSize(w, h));
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab