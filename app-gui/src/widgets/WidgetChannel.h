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

#include <functional>

#include <wx/tglbtn.h>
#include <wx/wx.h>

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

class WidgetChannel : public wxPanel
{
public:
    using ToggleChannelCb = std::function<void(const std::string& channel_name, bool state)>;

    WidgetChannel(wxWindow* parent, const std::string& name, bool state, ToggleChannelCb toggle_cb);
    void SetChannelState(bool state);

private:
    wxStaticText* label_;
    wxToggleButton* button_;
    ToggleChannelCb toggle_cb_;
};

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab