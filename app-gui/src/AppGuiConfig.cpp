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

#include "AppGuiConfig.h"

#include "cpp-utils/FileHelper.h"
#include "cpp-utils/StringHelper.h"
#include "nkh-lab/logger.hpp"

using namespace nkhlab::cpputils;

namespace nkhlab {
namespace usbrelaymodule {
namespace appgui {

AppGuiConfig::AppGuiConfig()
    : config_file_{}
    , app_start_pos_{wxDefaultPosition}
    , app_start_size_{wxDefaultSize}
    , app_min_size_{kAppMinSizeW, kAppMinSizeH}
    , is_hide_all_channels_page_{false}
{
    LOG_FNC;

    BuildAliasExample();
}

AppGuiConfig::AppGuiConfig(const std::string& config_file)
    : config_file_{config_file}
    , app_start_pos_{wxDefaultPosition}
    , app_start_size_{wxDefaultSize}
    , app_min_size_{kAppMinSizeW, kAppMinSizeH}
    , is_hide_all_channels_page_{false}
{
    LOG_FNC;

    if (FileHelper::ExistFile(config_file_))
        ReadConfigFromJsonStr(FileHelper::ReadFile(config_file_).str());
    else
        BuildAliasExample();
}

void AppGuiConfig::ReadConfigFromJsonStr(const std::string& str)
{
    LOG_FNC;

    Json::Value jroot;
    Json::Reader jreader;

    bool parsed = jreader.parse(str, jroot);

    if (parsed)
    {
        JsonToGeneralSettings(jroot);
        JsonToAliasSettings(jroot);
    }
}

std::string AppGuiConfig::WriteConfigToJsonStr()
{
    LOG_FNC;

    Json::Value jroot;

    GeneralSettingsToJson(jroot);
    AliasSettingsToJson(jroot);

    return Json::StyledWriter().write(jroot);
}

AppGuiConfig::~AppGuiConfig()
{
    LOG_FNC;

    if (!config_file_.empty()) FileHelper::WriteFile(config_file_, WriteConfigToJsonStr());
}

const wxSize& AppGuiConfig::GetAppStartSize()
{
    return app_start_size_;
}

const wxSize& AppGuiConfig::GetAppMinSize()
{
    return app_min_size_;
}

const wxPoint& AppGuiConfig::GetAppStartPosition()
{
    return app_start_pos_;
}

void AppGuiConfig::SetAppStartSize(const wxSize& size)
{
    LOG_DBG << StringHelper::Sprintf("w: %d, h: %d", size.GetWidth(), size.GetHeight());

    app_start_size_ = size;
}

void AppGuiConfig::SetAppStartPosition(const wxPoint& pos)
{
    LOG_DBG << StringHelper::Sprintf("x: %d, y: %d", pos.x, pos.y);

    app_start_pos_ = pos;
}

bool AppGuiConfig::IsHideAllChannelsPage()
{
    return is_hide_all_channels_page_;
}

const std::vector<AliasPage>& AppGuiConfig::GetAliasPages()
{
    return alias_pages_;
}

void AppGuiConfig::WriteConfigToFile()
{
    Json::Value jroot;

    GeneralSettingsToJson(jroot);
    AliasSettingsToJson(jroot);

    FileHelper::WriteFile(config_file_, Json::StyledWriter().write(jroot));
}

void AppGuiConfig::GeneralSettingsToJson(Json::Value& jroot)
{
    Json::Value jvalue;

    jvalue.append(app_start_pos_.x);
    jvalue.append(app_start_pos_.y);
    jroot[kJsonKeyAppStartPos] = jvalue;

    jvalue.clear();
    jvalue.append(app_start_size_.GetWidth());
    jvalue.append(app_start_size_.GetHeight());
    jroot[kJsonKeyAppStartSize] = jvalue;

    jvalue.clear();
    jvalue.append(app_min_size_.GetWidth());
    jvalue.append(app_min_size_.GetHeight());
    jroot[kJsonKeyAppMinSize] = jvalue;

    jroot[kJsonKeyHideAllChannelsPage] = is_hide_all_channels_page_;
}

void AppGuiConfig::AliasSettingsToJson(Json::Value& jroot)
{
    for (const auto& c : alias_colors_)
    {
        Json::Value jvalue;
        jvalue.append(c.second.Red());
        jvalue.append(c.second.Green());
        jvalue.append(c.second.Blue());
        jroot[kJsonKeyAliasColors][c.first] = jvalue;
    }

    for (const auto& p : alias_pages_)
    {
        Json::Value jp;
        jp[kJsonKeyAliasPageName] = p.page_name;

        for (const auto& c : p.channels)
        {
            Json::Value jc;
            jc[c.first].append(c.second.text);
            jc[c.first].append(c.second.state0.text);
            jc[c.first].append(c.second.state0.color_name);
            jc[c.first].append(c.second.state1.text);
            jc[c.first].append(c.second.state1.color_name);

            jp[kJsonKeyAliasChannels].append(jc);
        }

        jroot[kJsonKeyAliasPages].append(jp);
    }
}

void AppGuiConfig::ReadConfigFromFile()
{
    Json::Value jroot;

    FileHelper::ReadFile(config_file_) >> jroot;

    JsonToGeneralSettings(jroot);
    JsonToAliasSettings(jroot);
}

void AppGuiConfig::JsonToGeneralSettings(const Json::Value& jroot)
{
    if (jroot.isMember(kJsonKeyAppStartPos) && jroot[kJsonKeyAppStartPos].size() == 2)
    {
        try
        {
            int x, y;
            x = jroot[kJsonKeyAppStartPos][0].asInt();
            y = jroot[kJsonKeyAppStartPos][1].asInt();
            app_start_pos_ = {x, y};
        }
        catch (const std::exception& e)
        {
            LOG_ERR << e.what() << '\n';
        }
    }

    if (jroot.isMember(kJsonKeyAppStartSize) && jroot[kJsonKeyAppStartSize].size() == 2)
    {
        try
        {
            int w, h;
            w = jroot[kJsonKeyAppStartSize][0].asInt();
            h = jroot[kJsonKeyAppStartSize][1].asInt();
            app_start_size_ = {w, h};
        }
        catch (const std::exception& e)
        {
            LOG_ERR << e.what() << '\n';
        }
    }

    if (jroot.isMember(kJsonKeyAppMinSize) && jroot[kJsonKeyAppMinSize].size() == 2)
    {
        try
        {
            int w, h;
            w = jroot[kJsonKeyAppMinSize][0].asInt();
            h = jroot[kJsonKeyAppMinSize][1].asInt();
            app_min_size_ = {w, h};
        }
        catch (const std::exception& e)
        {
            LOG_ERR << e.what() << '\n';
        }
    }

    if (jroot.isMember(kJsonKeyHideAllChannelsPage))
    {
        try
        {
            is_hide_all_channels_page_ = jroot[kJsonKeyHideAllChannelsPage].asBool();
        }
        catch (const std::exception& e)
        {
            LOG_ERR << e.what() << '\n';
        }
    }
}

void AppGuiConfig::JsonToAliasSettings(const Json::Value& jroot)
{
    alias_colors_.clear();
    alias_pages_.clear();

    for (const std::string& k : jroot[kJsonKeyAliasColors].getMemberNames())
    {
        const Json::Value& v = jroot[kJsonKeyAliasColors][k];
        alias_colors_[k] = wxColor(v[0].asInt(), v[1].asInt(), v[2].asInt());

        LOG_DBG << StringHelper::Sprintf(
            "color: %s, (%d, %d, %d)", k.c_str(), v[0].asInt(), v[1].asInt(), v[2].asInt());
    }

    for (const Json::Value& jp : jroot[kJsonKeyAliasPages])
    {
        AliasPage p;
        p.page_name = jp[kJsonKeyAliasPageName].asString();

        for (const Json::Value& jc : jp[kJsonKeyAliasChannels])
        {
            const std::string k = jc.getMemberNames()[0];
            const Json::Value& v = jc[k];

            AliasChannel c;
            c.text = v[0].asString();
            std::string s_text = v[1].asString();
            std::string s_color_name = v[2].asString();
            c.state0 = {s_text, s_color_name, &alias_colors_[s_color_name]};
            s_text = v[3].asString();
            s_color_name = v[4].asString();
            c.state1 = {s_text, s_color_name, &alias_colors_[s_color_name]};

            p.channels.push_back(std::make_pair(k, c));
        }
        alias_pages_.push_back(p);
    }
}

void AppGuiConfig::BuildAliasExample()
{
    alias_colors_["green"] = *wxGREEN;
    alias_colors_["red"] = *wxRED;

    // DBG
    AliasChannel r1_1_channel;
    r1_1_channel.text = "Light";
    r1_1_channel.state0 = {"0", "green", &alias_colors_["green"]};
    r1_1_channel.state1 = {"1", "red", &alias_colors_["red"]};

    AliasChannel r1_2_channel;
    r1_2_channel.text = "PWR";
    r1_2_channel.state0 = {"ON", "green", &alias_colors_["green"]};
    r1_2_channel.state1 = {"OFF", "red", &alias_colors_["red"]};

    AliasPage alias_example_page;
    alias_example_page.page_name = "Alias Example";
    alias_example_page.channels.push_back(std::make_pair("R1_1", r1_1_channel));
    alias_example_page.channels.push_back(std::make_pair("R1_2", r1_2_channel));

    alias_pages_.push_back(alias_example_page);
}

} // namespace appgui
} // namespace usbrelaymodule
} // namespace nkhlab
