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

#include "WidgetPage.h"

#include "nkh-lab/logger.hpp"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

WidgetPage::WidgetPage(wxWindow* parent, ToggleChannelCb toggle_cb)
    : wxPanel(parent, wxID_ANY)
    , toggle_cb_{toggle_cb}
    , sizer_{new wxBoxSizer(wxVERTICAL)}
{
    LOG_FNC;
    this->SetSizer(sizer_);
}

bool WidgetPage::SetChannelState(const std::string& name, bool state)
{
    bool ret = false;

    // LOG_FNC;

    WidgetChannel* channel = DoesChannelExist(name);

    if (channel)
    {
        channel->SetChannelState(state);
        ret = true;
    }

    return ret;
}

WidgetChannel* WidgetPage::DoesChannelExist(const std::string& name)
{
    auto search = channels_.find(name);

    if (search != channels_.end()) return search->second;
    return nullptr;
}

bool WidgetPage::AddChannel(const std::string& name, bool state, AliasChannel* alias_channel)
{
    bool ret = false;

    LOG_FNC;

    if (!DoesChannelExist(name))
    {
        WidgetChannel* widget = new WidgetChannel(
            this,
            name,
            state,
            [&](const std::string& channel_name, bool state) {
                LOG_FNC;

                if (toggle_cb_) toggle_cb_(channel_name, state);
            },
            alias_channel);
        sizer_->AddSpacer(10);
        sizer_->Add(widget);

        channels_[name] = widget;
        ret = true;

        this->SetSizerAndFit(sizer_);
    }

    return ret;
}

bool WidgetPage::RemoveChannel(const std::string& /*name*/)
{
    LOG_FNC;

    return true;
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
