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

#include <wx/notebook.h>
#include <wx/wx.h>

#include "widgets/WidgetPage.h"
#include "widgets/WidgetStatusBar.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

class MainWindow : public wxFrame
{
public:
    MainWindow(
        wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& start_pos,
        const wxSize& start_size,
        const wxSize& min_size,
        bool stay_on_top);
    ~MainWindow();

    wxWindow* GetPageParent();
    void AddPage(WidgetPage* page);
    const std::vector<WidgetPage*>& GetPages();
    bool IsStayOnTopChecked();

private:
    void AddIcon();
    void BuildMenuBar();
    void BuildStatusBar(bool stay_on_top);
    void StayOnTop(bool stay);

    wxNotebook* notebook_;
    std::vector<WidgetPage*> pages_;
    WidgetStatusBar* status_bar_;
};

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
