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

#include <wx/mstream.h>

#include "cpp-utils/Macros.h"
#include "nkh-lab/logger.hpp"
#include "widgets/WidgetAboutDialog.h"

#ifdef __linux__
// Load the icon data from the object file
extern const char _binary_icon_png_start[];
extern const char _binary_icon_png_end[];
#endif

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

MainWindow::MainWindow(
    wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& start_pos,
    const wxSize& start_size,
    const wxSize& min_size,
    bool stay_on_top)
    : wxFrame(parent, id, title, start_pos, start_size, wxDEFAULT_FRAME_STYLE, wxFrameNameStr)
{
    LOG_FNC;

    AddIcon();

    SetMinSize(min_size);

    BuildMenuBar();
    BuildStatusBar(stay_on_top);

    notebook_ = new wxNotebook(this, wxID_ANY);
}

MainWindow::~MainWindow()
{
    LOG_FNC;
}

void MainWindow::AddIcon()
{
#ifdef __linux__
    wxImage::AddHandler(new wxPNGHandler());

    wxMemoryInputStream stream(_binary_icon_png_start, _binary_icon_png_end - _binary_icon_png_start);
    wxImage png(stream, wxBITMAP_TYPE_PNG);
    wxIcon icon;
    icon.CopyFromBitmap(wxBitmap(png));
#else
    wxIcon icon = wxICON(IDI_APPLICATION);
#endif

    SetIcon(icon);
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

void MainWindow::BuildStatusBar(bool stay_on_top)
{
    wxStatusBar* status_bar = new wxStatusBar(this);
    on_top_check_box_ = new wxCheckBox(status_bar, wxID_ANY, "Stay on top");

    on_top_check_box_->SetValue(stay_on_top);
    StayOnTop(stay_on_top);

    on_top_check_box_->Bind(wxEVT_CHECKBOX, [&](wxCommandEvent& event) {
        UNUSED(event);

        StayOnTop(on_top_check_box_->IsChecked());
    });

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->AddSpacer(5);

    sizer->Add(on_top_check_box_, 0, wxALIGN_CENTER_VERTICAL);

    status_bar->SetSizer(sizer);

    SetStatusBar(status_bar);
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

void MainWindow::StayOnTop(bool stay)
{
    long style = GetWindowStyleFlag();

    if (stay)
    {
        SetWindowStyleFlag(style | wxSTAY_ON_TOP);
    }
    else
    {
        SetWindowStyleFlag(style & ~wxSTAY_ON_TOP);
    }
}

bool MainWindow::IsStayOnTopChecked()
{
    return on_top_check_box_->IsChecked();
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
