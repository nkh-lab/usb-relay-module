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

#include "WidgetStatusBar.h"

#include "cpp-utils/Macros.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

constexpr int kFieldsCount = 2;
// The 0 field is used by default for tooltip text, for example, when navigating the menu bar
constexpr int kStayOnTopFieldIdx = 1;

WidgetStatusBar::WidgetStatusBar(wxWindow* parent, bool init_stay_on_top_state, StayOnTopToggleCb stay_on_top_toggle_cb)
    : wxStatusBar(parent)
{
    SetFieldsCount(kFieldsCount);

    stay_on_top_check_box_ = new wxCheckBox(this, wxID_ANY, "Stay on top");

    stay_on_top_check_box_->SetValue(init_stay_on_top_state);

    stay_on_top_check_box_->Bind(wxEVT_CHECKBOX, [&, stay_on_top_toggle_cb](wxCommandEvent& event) {
        UNUSED(event);

        stay_on_top_toggle_cb(stay_on_top_check_box_->IsChecked());
    });

    Bind(wxEVT_SIZE, [&](wxSizeEvent& event) {
        UNUSED(event);
        wxRect rect;
        GetFieldRect(kStayOnTopFieldIdx, rect);
        auto pos = rect.GetPosition();
        pos.x = pos.x + (rect.GetSize().GetWidth() - stay_on_top_check_box_->GetSize().GetWidth());

        stay_on_top_check_box_->SetPosition(pos);
    });
}

bool WidgetStatusBar::IsStayOnTopChecked()
{
    return stay_on_top_check_box_->IsChecked();
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
