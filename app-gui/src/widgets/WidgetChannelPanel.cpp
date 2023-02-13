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

#include "WidgetChannelPanel.h"

#include "nkh-lab/logger.hpp"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

WidgetChannelPanel::WidgetChannelPanel(wxWindow* parent, ToggleChannelCb toggle_cb)
    : wxPanel(parent, wxID_ANY)
    , toggle_cb_{toggle_cb}
    , sizer_{new wxBoxSizer(wxVERTICAL)}
{
    LOG_FNC;
    this->SetSizer(sizer_);
}

bool WidgetChannelPanel::SetChannelState(const std::string& name, bool state)
{
    bool ret = false;

    //LOG_FNC;

    if(DoesChannelExist(name))
    {
        channels_[name]->SetChannelState(state);
        ret = true;
    }

    return ret;
}

bool WidgetChannelPanel::DoesChannelExist(const std::string& name)
{
    bool ret = false;

    //LOG_FNC;

    if ( channels_.find(name) != channels_.end()) ret = true;

    return ret;
}

bool WidgetChannelPanel::AddChannel(const std::string& name, bool state)
{
    bool ret = false;

    LOG_FNC;

    if(!DoesChannelExist(name))
    {
        WidgetChannel* widget = new WidgetChannel(this, name, state, [&](const std::string& channel_name, bool state) {
            LOG_FNC;

            if(toggle_cb_) toggle_cb_(channel_name, state);
        });
        sizer_->AddSpacer(10);
        sizer_->Add(widget);

        channels_[name]=widget;
        ret = true;

        this->SetSizerAndFit(sizer_);
    }

    return ret;
}

bool WidgetChannelPanel::RemoveChannel(const std::string& /*name*/)
{
    LOG_FNC;

    return true;
}

}
}
}
