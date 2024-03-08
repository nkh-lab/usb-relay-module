/*
 * Copyright (C) 2024 https://github.com/nkh-lab
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

class WidgetStatusBar : public wxStatusBar
{
public:
    using StayOnTopToggleCb = std::function<void(bool state)>;

    WidgetStatusBar(wxWindow* parent, bool init_stay_on_top_state, StayOnTopToggleCb stay_on_top_toggle_cb);

    ~WidgetStatusBar() = default;

    bool IsStayOnTopChecked();

private:
    wxCheckBox* stay_on_top_check_box_;
};

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab