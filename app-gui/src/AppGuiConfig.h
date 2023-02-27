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
#include <wx/wx.h>

#include "Alias.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

constexpr int kAppMinSizeW = 250;
constexpr int kAppMinSizeH = 300;

constexpr char kJsonKeyAppStartPos[] = "appStartPosition";
constexpr char kJsonKeyAppStartSize[] = "appStartSize";
constexpr char kJsonKeyAppMinSize[] = "appMinSize";
constexpr char kJsonKeyHideAllChannelsPage[] = "hideAllChannelsPage";
constexpr char kJsonKeyAliasColors[] = "aliasColors";
constexpr char kJsonKeyAliasPages[] = "aliasPages";
constexpr char kJsonKeyAliasPageName[] = "name";
constexpr char kJsonKeyAliasChannels[] = "channels";

class AppGuiConfig
{
public:
    AppGuiConfig();
    AppGuiConfig(const std::string& config_file);
    ~AppGuiConfig();

    void ReadConfigFromJsonStr(const std::string& str);
    std::string WriteConfigToJsonStr();

    const wxSize& GetAppStartSize();
    const wxSize& GetAppMinSize();
    const wxPoint& GetAppStartPosition();

    void SetAppStartSize(const wxSize& size);
    void SetAppStartPosition(const wxPoint& pos);

    bool IsHideAllChannelsPage();
    const std::vector<AliasPage>& GetAliasPages();

private:
    void WriteConfigToFile();
    void ReadConfigFromFile();
    void BuildAliasExample();
    void GeneralSettingsToJson(Json::Value& jroot);
    void AliasSettingsToJson(Json::Value& jroot);
    void JsonToGeneralSettings(const Json::Value& jroot);
    void JsonToAliasSettings(const Json::Value& jroot);

    std::string config_file_;
    wxPoint app_start_pos_;
    wxSize app_start_size_;
    wxSize app_min_size_;
    bool is_hide_all_channels_page_;
    std::map<std::string, wxColor> alias_colors_;
    std::vector<AliasPage> alias_pages_;
};

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
