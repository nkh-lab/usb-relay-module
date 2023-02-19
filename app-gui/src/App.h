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

#include <memory>
#include <mutex>
#include <vector>

#include <wx/app.h>
#include <wx/timer.h>

#include "Alias.h"
#include "AppGuiConfig.h"
#include "MainWindow.h"
#include "RelayManager.h"
#include "widgets/WidgetPage.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

class App : public wxApp
{
public:
    App();
    ~App();

    bool OnInit() override;
    int OnExit() override;

private:
    void OnChannelToggled(const std::string& channel_name, bool state);
    void OnUpdateTimeout(wxTimerEvent& event);
    void OnMainWindowClose(wxCloseEvent& event);
    WidgetPage* CreateAllChannelsPage(wxWindow* parent);
    WidgetPage* CreateAliasPage(wxWindow* parent, const AliasPage& alias_page);

    std::mutex mutex_;
    IRelayManagerPtr relay_manager_;
    std::vector<AliasPage> aliases_;
    MainWindow* main_window_;
    wxTimer update_timer_;
    std::unique_ptr<AppGuiConfig> config_;
};

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
