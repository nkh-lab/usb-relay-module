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

#include <algorithm>

#include "cpp-utils/StringHelper.h"
#include "nkh-lab/logger.hpp"

using namespace nkhlab::cpputils;

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

WidgetPage::WidgetPage(wxWindow* parent, const std::string& name, ToggleChannelCb toggle_cb)
    : wxPanel(parent, wxID_ANY)
    , name_{name}
    , toggle_cb_{toggle_cb}
    , sizer_{new wxBoxSizer(wxVERTICAL)}
{
    LOG_FNC;

    this->SetSizer(sizer_);
}

const std::string& WidgetPage::GetName()
{
    return name_;
}

bool WidgetPage::SetChannelState(const std::string& name, bool state)
{
    // LOG_FNC;

    bool ret = false;
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
    WidgetChannel* ret = nullptr;

    auto it =
        std::find_if(widget_channels_.begin(), widget_channels_.end(), [&](const WidgetChannel* wc) {
            return wc->GetChannelName() == name;
        });

    if (it != widget_channels_.end()) ret = *it;

    return ret;
}

bool WidgetPage::AddChannel(const std::string& name, bool state, AliasChannel* alias_channel)
{
    LOG_FNC;

    bool ret = false;

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

        widget_channels_.push_back(widget);
        ret = true;

        this->SetSizerAndFit(sizer_);
    }

    return ret;
}

void WidgetPage::RemoveAllChannels()
{
    LOG_FNC;

    DestroyChildren();
    sizer_->Clear();
    widget_channels_.clear();
}

const std::vector<WidgetChannel*>& WidgetPage::GetAllChannels() const
{
    return widget_channels_;
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
