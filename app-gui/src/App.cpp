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

#include "App.h"

#include <iostream>

#include <wx/textctrl.h>

#include "MainWindow.h"
#include "Utils.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

App::App()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

bool App::OnInit()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    bool ret = false;

    if (wxApp::OnInit())
    {
#ifdef URM_SIMU
        std::string path = argv[0].ToStdString();
        std::size_t found = path.find_last_of("/\\") + 1;
        path = path.substr(0, found);
        relay_manager_ = CreateSimuManager(path);
#else
        relay_manager_ = CreateHidapiManagerForDcttechModules();
#endif

        // acording to wxWidjets spec window is suicide object, and we mast not use delete operator
        MainWindow* m = new MainWindow(nullptr, wxID_ANY, "Hello World Title");
        m->Show();

        wxTextCtrl* text_ctrl = new wxTextCtrl(
            m,
            wxID_ANY,
            wxEmptyString,
            wxDefaultPosition,
            wxDefaultSize,
            wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

        wxFont font = text_ctrl->GetFont();
        font.SetFamily(wxFONTFAMILY_TELETYPE);
        text_ctrl->SetFont(font);

        for (auto m : relay_manager_->GetModules())
        {
            *text_ctrl << m->GetInfo();
            *text_ctrl << "\n";
        }

        ret = true;
    }

    return ret;
}

int App::OnExit()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    return wxApp::OnExit();
}

App::~App()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
