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

#include <wx/wx.h>

#include "Alias.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

class AppGuiConfig
{
public:
    AppGuiConfig(const std::string& config_file);
    ~AppGuiConfig();

    const wxSize& GetAppStartSize();
    const wxSize& GetAppMinSize();
    const wxPoint& GetAppStartPosition();

    void SetAppStartSize(const wxSize& size);
    void SetAppStartPosition(const wxPoint& pos);

    bool IsHideAllChannelsPage();
    std::vector<AliasPage> GetAliasPages();

private:
    void WriteConfigToFile();
    void ReadConfigFromFile();
    void BuildAliasExample();

    std::string config_file_;
    wxPoint app_start_pos_;
    wxSize app_start_size_;
    wxSize app_min_size_;
    bool is_hide_all_channels_page_;
    std::map<std::string, wxColor> alias_colors_;
};

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
