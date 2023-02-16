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

#include "nkh-lab/logger.hpp"

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

    notebook_ = new wxNotebook(this, wxID_ANY);
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
