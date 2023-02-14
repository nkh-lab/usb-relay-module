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

#include <array>
#include <functional>
#include <string>

#include <wx/colour.h>
#include <wx/tglbtn.h>
#include <wx/wx.h>

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

class WidgetToggleButton : public wxToggleButton
{
public:
    using WidgetButtonToggleCb = std::function<void(bool state)>;

    WidgetToggleButton(
        wxWindow* parent,
        bool init_state,
        WidgetButtonToggleCb toggle_cb,
        const std::string& state0_label = "0",
        wxColor* state0_color = nullptr,
        const std::string& state1_label = "1",
        wxColor* state1_color = nullptr);

private:
    void StyleState(bool state);

    const std::string state0_label_;
    const wxColor* state0_color_;
    const std::string state1_label_;
    const wxColor* state1_color_;
};

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab