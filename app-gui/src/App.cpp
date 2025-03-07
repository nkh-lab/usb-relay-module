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

#include <wx/cmdline.h>

#include "RelayManagerHelper.h"
#include "cpp-utils/FileHelper.h"
#include "cpp-utils/Macros.h"
#include "cpp-utils/StringHelper.h"
#include "nkh-lab/logger.hpp"
#include "widgets/WidgetChannel.h"

using namespace nkhlab::cpputils;

std::mutex nlab::logger::gCoutMutex;

namespace {
constexpr int kUpdateTime_ms = 1000;
}

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
        std::string app_file = argv[0].ToStdString();
        std::string app_path = FileHelper::GetDir(app_file);
        std::string app_name = FileHelper::GetFileName(app_file);
        if (config_file_.empty())
            config_file_ = FileHelper::RemoveFileExtension(app_file) + "-cfg.json";

        LOG_INF << StringHelper::Sprintf("app_file:    %s", app_file.c_str());
        LOG_INF << StringHelper::Sprintf("config_file: %s", config_file_.c_str());

#ifdef URM_SIMU
        relay_manager_ = CreateSimuManager(app_path);
#else
        relay_manager_ = CreateHidapiManagerForDcttechModules();
#endif
        config_ = std::make_unique<AppGuiConfig>(config_file_);

        main_window_ = new MainWindow(
            nullptr,
            wxID_ANY,
            "Relay Box",
            config_->GetAppStartPosition(),
            config_->GetAppStartSize(),
            config_->GetAppMinSize(),
            config_->IsAppStayOnTop());
        auto page_parent = main_window_->GetPageParent();
        main_window_->Bind(wxEVT_CLOSE_WINDOW, &App::OnMainWindowClose, this);

        auto channels = RelayManagerHelper::GetAllChannels(relay_manager_.get());

        if (!config_->IsHideAllChannelsPage())
            main_window_->AddPage(CreateAllChannelsPage(page_parent, channels));

        for (auto p : config_->GetAliasPages())
        {
            main_window_->AddPage(CreateAliasPage(page_parent, p, channels));
        }

        main_window_->Show();

        update_timer_.Bind(wxEVT_TIMER, &App::OnUpdateTimeout, this);
        update_timer_.Start(kUpdateTime_ms, true);

        ret = true;
    }

    return ret;
}

void App::OnInitCmdLine(wxCmdLineParser& parser)
{
    LOG_FNC;

    const wxCmdLineEntryDesc cmds[] = {
        {wxCMD_LINE_SWITCH, "h", "help", "Display this help text", wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP},
        {wxCMD_LINE_OPTION, "c", "config", "Path to config file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},

        wxCMD_LINE_DESC_END};

    parser.SetDesc(cmds);
}

bool App::OnCmdLineParsed(wxCmdLineParser& parser)
{
    LOG_FNC;

    wxString config_file;

    if (parser.Found("config", &config_file)) config_file_ = config_file.ToStdString();
    return true;
}

void App::OnMainWindowClose(wxCloseEvent& event)
{
    LOG_FNC;

    auto rect = main_window_->GetRect();
    config_->SetAppStartPosition(rect.GetPosition());
    config_->SetAppStartSize(rect.GetSize());
    config_->SetAppStayOnTop(main_window_->IsStayOnTopChecked());

    event.Skip(); // Allow the frame to close normally
}

void App::OnChannelToggled(const std::string& channel_name, bool state)
{
    std::lock_guard<std::mutex> lock(mutex_);

    LOG_INF << StringHelper::Sprintf(
        "channel_name: %s, state: %d", channel_name.c_str(), static_cast<int>(state));

    RelayManagerHelper::SetChannel(relay_manager_.get(), channel_name, state);
}

void App::OnUpdateTimeout(wxTimerEvent& event)
{
    // LOG_FNC;

    UNUSED(event);

    std::lock_guard<std::mutex> lock(mutex_);

    auto channels = RelayManagerHelper::GetAllChannels(relay_manager_.get());

    for (const auto& p : main_window_->GetPages())
    {
        if (p == *main_window_->GetPages().cbegin() && !config_->IsHideAllChannelsPage())
        {
            if (!UpdateAllChannelsPage(p, channels))
            {
                p->RemoveAllChannels();
                AddChannelsToAllChannelsPage(p, channels);
            }
        }
        else
            UpdateAliasPage(p, channels);
    }

    update_timer_.Start(kUpdateTime_ms, true);
}

WidgetPage* App::CreateAllChannelsPage(wxWindow* parent, const std::map<std::string, bool>& channels)
{
    LOG_FNC;

    WidgetPage* page =
        new WidgetPage(parent, "All channels", std::bind(&App::OnChannelToggled, this, _1, _2));

    AddChannelsToAllChannelsPage(page, channels);

    return page;
}

void App::AddChannelsToAllChannelsPage(WidgetPage* page, const std::map<std::string, bool>& channels)
{
    LOG_FNC;

    for (const auto& c : channels)
    {
        page->AddChannel(c.first, c.second);
    }
}

WidgetPage* App::CreateAliasPage(
    wxWindow* parent,
    const AliasPage& alias_page,
    const std::map<std::string, bool>& channels)
{
    LOG_FNC;

    WidgetPage* page =
        new WidgetPage(parent, alias_page.page_name, std::bind(&App::OnChannelToggled, this, _1, _2));

    for (auto c : alias_page.channels)
    {
        page->AddChannel(c.first, false, &c.second);
    }

    UpdateAliasPage(page, channels);

    return page;
}

void App::UpdateAliasPage(WidgetPage* page, const std::map<std::string, bool>& channels)
{
    for (const auto& wc : page->GetAllChannels())
    {
        const auto& name = wc->GetChannelName();

        if (channels.count(name))
        {
            wc->SetChannelState(channels.at(name));
            wc->Enable(true);
        }
        else
        {
            wc->SetChannelState(false);
            wc->Enable(false);
        }
    }
}

bool App::UpdateAllChannelsPage(WidgetPage* page, const std::map<std::string, bool>& channels)
{
    auto page_channel_size = page->GetAllChannels().size();
    auto manager_channel_size = channels.size();

    if (page_channel_size != manager_channel_size)
    {
        LOG_WRN << StringHelper::Sprintf(
            "page_channel_size: %d != manager_channel_size: %d", page_channel_size, manager_channel_size);
        return false;
    }

    for (const auto& wc : page->GetAllChannels())
    {
        const auto& name = wc->GetChannelName();

        if (channels.count(name))
        {
            wc->SetChannelState(channels.at(name));
        }
        else
        {
            LOG_WRN << StringHelper::Sprintf("No '%s' found", name.c_str());
            return false;
        }
    }

    return true;
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
