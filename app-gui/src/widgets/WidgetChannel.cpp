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

#include "WidgetChannel.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

WidgetChannel::WidgetChannel(
    wxWindow* parent,
    const std::string& name,
    bool state,
    ToggleChannelCb toggle_cb,
    AliasChannel* alias)
    : wxPanel(parent, wxID_ANY)
{
    label_ = new wxStaticText(this, wxID_ANY, alias ? alias->text : name);
    label_->SetMinSize(wxSize(100, -1)); // set width to 200 pixels
    button_ = new WidgetToggleButton(
        this,
        state,
        [name, toggle_cb](bool state) {
            if (toggle_cb) toggle_cb(name, state);
        },
        alias ? alias->state0.text : "0",
        alias ? alias->state0.color : nullptr,
        alias ? alias->state1.text : "1",
        alias ? alias->state1.color : nullptr);

    // Use a box sizer to arrange the controls inside the panel
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->AddSpacer(10);
    sizer->Add(label_, 0, wxALIGN_CENTER_VERTICAL);
    sizer->AddSpacer(10);
    sizer->Add(button_, 0, wxALIGN_CENTER_VERTICAL);

    this->SetSizerAndFit(sizer);
}

void WidgetChannel::SetChannelState(bool state)
{
    if (button_->GetState() != state)
    {
        button_->SetState(state);
    }
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
