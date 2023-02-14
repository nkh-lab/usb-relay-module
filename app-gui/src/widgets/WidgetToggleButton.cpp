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

#include "WidgetToggleButton.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

WidgetToggleButton::WidgetToggleButton(
    wxWindow* parent,
    bool init_state,
    WidgetButtonToggleCb toggle_cb,
    const std::string& state0_label,
    wxColor* state0_color,
    const std::string& state1_label,
    wxColor* state1_color)
    : wxToggleButton(parent, wxID_ANY, "")
    , state0_label_{state0_label}
    , state0_color_{state0_color ? state0_color : wxGREEN}
    , state1_label_{state1_label}
    , state1_color_{state1_color ? state0_color : wxRED}
{
    StyleState(init_state);

    Bind(wxEVT_TOGGLEBUTTON, [&, toggle_cb](wxCommandEvent& event) {
        bool state = event.IsChecked();
        StyleState(state);
        if (toggle_cb) toggle_cb(state);
    });
}

void WidgetToggleButton::StyleState(bool state)
{
    if (state)
    {
        SetLabel(state1_label_);
        SetBackgroundColour(*state1_color_);
    }
    else
    {
        SetLabel(state0_label_);
        SetBackgroundColour(*state0_color_);
    }
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
