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

#include <iostream>

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
}

MainWindow::~MainWindow()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
