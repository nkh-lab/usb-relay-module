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

#include "MainWindow.h"

#include "Utils.h"
#include "nkh-lab/logger.hpp"
#include "widgets/WidgetAboutDialog.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

MainWindow::MainWindow(
    wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name)
    : wxFrame(parent, id, title, pos, size, style, name)
{
    LOG_FNC;

    BuildMenuBar();

    notebook_ = new wxNotebook(this, wxID_ANY);
}

void MainWindow::BuildMenuBar()
{
    wxMenu* help_menu = new wxMenu();
    help_menu->Append(wxID_ABOUT, "About");

    Bind(
        wxEVT_MENU,
        [&](wxCommandEvent& event) {
            UNUSED(event);
            WidgetAboutDialog about(this); // not self suicide object
            about.ShowModal();
        },
        wxID_ABOUT);

    wxMenuBar* menu_bar = new wxMenuBar;
    menu_bar->Append(help_menu, "Help");

    SetMenuBar(menu_bar);
}

wxWindow* MainWindow::GetPageParent()
{
    return notebook_;
}

void MainWindow::AddPage(WidgetPage* page)
{
    page->SetParent(notebook_);
    notebook_->AddPage(page, page->GetName());
    pages_.push_back(page);
}

const std::vector<WidgetPage*>& MainWindow::GetPages()
{
    return pages_;
}

MainWindow::~MainWindow()
{
    LOG_FNC;
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
