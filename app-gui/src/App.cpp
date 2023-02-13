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

#include <wx/notebook.h>
#include <wx/textctrl.h>

#include "MainWindow.h"
#include "RelayManagerHelper.h"
#include "Utils.h"
#include "nkh-lab/logger.hpp"
#include "widgets/WidgetChannel.h"

std::mutex nlab::logger::gCoutMutex;

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

App::App()
{
    LOG_FNC;
}

bool App::OnInit()
{
    LOG_FNC;

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
        MainWindow* main_window = new MainWindow(nullptr, wxID_ANY, "Relay Box");
        main_window->Show();

        wxNotebook* notebook = new wxNotebook(main_window, wxID_ANY);

        // Add pages to the notebook
        channel_panel_ =
            new WidgetChannelPanel(notebook, [&](const std::string& channel_name, bool state) {
                std::lock_guard<std::mutex> lock(mutex_);

                LOG_INF << utils::Sprintf(
                    "channel_name: %s, state: %d", channel_name.c_str(), static_cast<int>(state));

                RelayManagerHelper::SetChannel(relay_manager_.get(), channel_name, state);
            });
        notebook->AddPage(channel_panel_, "All channels");

        auto modules = relay_manager_->GetModules();

        for (auto m : modules)
        {
            std::string module_name;
            std::vector<bool> channels;

            m->GetNameAndChannels(module_name, channels);

            for (size_t c = 0; c < channels.size(); ++c)
            {
                channel_panel_->AddChannel(
                    utils::Sprintf("%s_%d", module_name.c_str(), c + 1), channels[c]);
            }
        }

        auto on_update_timeout = [&](wxTimerEvent& event) {
            std::lock_guard<std::mutex> lock(mutex_);

            UNUSED(event);

            auto modules = relay_manager_->GetModules();

            for (auto m : modules)
            {
                std::string module_name;
                std::vector<bool> channels;

                m->GetNameAndChannels(module_name, channels);

                for (size_t c = 0; c < channels.size(); ++c)
                {
                    channel_panel_->SetChannelState(
                        utils::Sprintf("%s_%d", module_name.c_str(), c + 1), channels[c]);
                }
            }
        };

        Bind(wxEVT_TIMER, on_update_timeout, update_timer_.GetId());
        update_timer_.Start(100);

        ret = true;
    }

    return ret;
}

int App::OnExit()
{
    LOG_FNC;

    return wxApp::OnExit();
}

App::~App()
{
    LOG_FNC;
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
