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

#include "MainWindow.h"
#include "RelayManagerHelper.h"
#include "Utils.h"
#include "nkh-lab/logger.hpp"
#include "widgets/WidgetChannel.h"

std::mutex nlab::logger::gCoutMutex;

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

using namespace std::placeholders;

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

        notebook_ = new wxNotebook(main_window, wxID_ANY);

        notebook_->AddPage(CreateAllChannelsPage(notebook_), "All channels");

        // DBG
        AliasChannel power_channel;
        power_channel.text = "PWR";
        power_channel.state0 = {"ON", wxGREEN};
        power_channel.state1 = {"OFF", wxRED};

        AliasChannel qfil_channel;
        qfil_channel.text = "QFIL";
        qfil_channel.state0 = {"OFF", wxGREEN};
        qfil_channel.state1 = {"ON", wxRED};

        AliasChannel vip_channel;
        vip_channel.text = "VIP ";
        vip_channel.state0 = {"OFF", wxGREEN};
        vip_channel.state1 = {"ON", wxRED};

        AliasPage rig_page;
        rig_page.page_name = "Rig";
        rig_page.chanels.push_back(std::make_pair("R1_2", power_channel));
        rig_page.chanels.push_back(std::make_pair("R1_1", qfil_channel));
        rig_page.chanels.push_back(std::make_pair("R2_1", vip_channel));

        aliases_.push_back(rig_page);
        //

        for (auto p : aliases_)
        {
            notebook_->AddPage(CreateAliasPage(notebook_, p), p.page_name);
        }

        main_window->Show();

        Bind(wxEVT_TIMER, &App::OnUpdateTimeout, this, update_timer_.GetId());
        update_timer_.Start(100);

        ret = true;
    }

    return ret;
}

void App::OnChannelToggled(const std::string& channel_name, bool state)
{
    std::lock_guard<std::mutex> lock(mutex_);

    LOG_INF << utils::Sprintf(
        "channel_name: %s, state: %d", channel_name.c_str(), static_cast<int>(state));

    RelayManagerHelper::SetChannel(relay_manager_.get(), channel_name, state);
}

void App::OnUpdateTimeout(wxTimerEvent& event)
{
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
            for (size_t p = 0; p < notebook_->GetPageCount(); ++p)
            {
                WidgetPage* page = reinterpret_cast<WidgetPage*>(notebook_->GetPage(p));

                page->SetChannelState(
                    utils::Sprintf("%s_%d", module_name.c_str(), c + 1), channels[c]);
            }
        }
    }
}

WidgetPage* App::CreateAllChannelsPage(wxWindow* parent)
{
    WidgetPage* page = new WidgetPage(parent, std::bind(&App::OnChannelToggled, this, _1, _2));

    auto modules = relay_manager_->GetModules();

    for (auto m : modules)
    {
        std::string module_name;
        std::vector<bool> channels;

        m->GetNameAndChannels(module_name, channels);

        for (size_t c = 0; c < channels.size(); ++c)
        {
            page->AddChannel(utils::Sprintf("%s_%d", module_name.c_str(), c + 1), channels[c]);
        }
    }

    return page;
}

WidgetPage* App::CreateAliasPage(wxWindow* parent, const AliasPage& alias_page)
{
    WidgetPage* page = new WidgetPage(parent, std::bind(&App::OnChannelToggled, this, _1, _2));

    for (auto c : alias_page.chanels)
    {
        page->AddChannel(c.first, false, &c.second);
    }

    return page;
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
