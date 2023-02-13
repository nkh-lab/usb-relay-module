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
#include <mutex>
#include <map>

#include <wx/wx.h>
#include "WidgetChannel.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

class WidgetChannelPanel : public wxPanel
{
public:
    using ToggleChannelCb = std::function<void(const std::string& channel_name, bool state)>;

    WidgetChannelPanel(wxWindow* parent, ToggleChannelCb toggle_cb);
    bool SetChannelState(const std::string& name, bool state);
    bool DoesChannelExist(const std::string& name);
    bool AddChannel(const std::string& name, bool state);
    bool RemoveChannel(const std::string& name);
private:
    std::map<std::string, WidgetChannel*> channels_;
    ToggleChannelCb toggle_cb_;
    wxBoxSizer* sizer_;
};

}
}
}