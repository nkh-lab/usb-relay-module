
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

#include <wx/wx.h>

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

class WidgetHelper
{
public:
    WidgetHelper() = delete;

    static void FreezeSize(wxWindow* widget)
    {
        if (!widget) return;

        wxSize size = widget->GetSize();
        widget->SetMinSize(size);
        widget->SetMaxSize(size);
    }
};

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab