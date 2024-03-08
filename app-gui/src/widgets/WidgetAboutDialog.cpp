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

#include "WidgetAboutDialog.h"

#include <wx/hyperlink.h>

#include "Config.h"
#include "cpp-utils/Macros.h"
#include "cpp-utils/StringHelper.h"
#include "nkh-lab/logger.hpp"
#include "widgets/WidgetHelper.h"

using namespace nkhlab::cpputils;

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

constexpr char kProjectUrl[] = "https://github.com/nkh-lab/usb-relay-module";

constexpr char kAboutText[] =
    "Version: %d.%d.%d\n"
    "Commit: %s\n"
    "\n"
    "Copyright (C) 2024 https://github.com/nkh-lab\n"
    "This is free software under GPL-3.0 license.\n";

WidgetAboutDialog::WidgetAboutDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Relay Box")
{
    LOG_FNC;

    wxHyperlinkCtrl* project_link = new wxHyperlinkCtrl(this, wxID_ANY, kProjectUrl, kProjectUrl);
    project_link->SetCanFocus(false);

    wxStaticText* text = new wxStaticText(
        this,
        wxID_ANY,
        StringHelper::Sprintf(
            kAboutText,
            config::kProjectVerMajor,
            config::kProjectVerMinor,
            config::kProjectVerPatch,
            config::kGitCommitHash));

    wxButton* ok_btn = new wxButton(this, wxID_OK, "OK");

    ok_btn->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        UNUSED(event);
        EndModal(wxID_OK);
    });

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(project_link, 0, wxALL, 10);
    sizer->Add(text, 0, wxALL, 10);
    sizer->Add(ok_btn, 0, wxALL | wxALIGN_CENTER, 10);

    SetSizerAndFit(sizer);

    WidgetHelper::FreezeSize(this);
}

WidgetAboutDialog::~WidgetAboutDialog()
{
    LOG_FNC;
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab