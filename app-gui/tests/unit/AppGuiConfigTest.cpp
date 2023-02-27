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

#include <gtest/gtest.h>

#include "AppGuiConfig.h"

using namespace nkhlab::usbrelaymodule::appgui;

TEST(AppGuiConfigTest, HideAllChannelsPageEmpty)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr("{}");
    EXPECT_FALSE(cfg.IsHideAllChannelsPage());
}

TEST(AppGuiConfigTest, HideAllChannelsPageFalse)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"hideAllChannelsPage" : false})");
    EXPECT_FALSE(cfg.IsHideAllChannelsPage());
}

TEST(AppGuiConfigTest, HideAllChannelsPageTrue)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"hideAllChannelsPage" : true})");
    EXPECT_TRUE(cfg.IsHideAllChannelsPage());
}

TEST(AppGuiConfigTest, HideAllChannelsPageException)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"hideAllChannelsPage" : "exception"})");
    EXPECT_FALSE(cfg.IsHideAllChannelsPage());
}

TEST(AppGuiConfigTest, AppStartSizeEmpty)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr("{}");
    EXPECT_EQ(wxDefaultSize.GetWidth(), cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(wxDefaultSize.GetHeight(), cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartSizePositive)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appStartSize" : [ 250, 300 ]})");
    EXPECT_EQ(250, cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(300, cfg.GetAppStartSize().GetHeight());
    ;
}

TEST(AppGuiConfigTest, AppStartSizeNegative1)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appStartSize" : [ 300 ]})");
    EXPECT_EQ(wxDefaultSize.GetWidth(), cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(wxDefaultSize.GetHeight(), cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartSizeNegative3)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appStartSize" : [ 250, 300, 400 ]})");
    EXPECT_EQ(wxDefaultSize.GetWidth(), cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(wxDefaultSize.GetHeight(), cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartSizeException)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appStartSize" : [ 250, "exception" ]})");
    EXPECT_EQ(wxDefaultSize.GetWidth(), cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(wxDefaultSize.GetHeight(), cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizeEmpty)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr("{}");
    EXPECT_EQ(kAppMinSizeW, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(kAppMinSizeH, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizePositive)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appMinSize" : [ 250, 300 ]})");
    EXPECT_EQ(250, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(300, cfg.GetAppMinSize().GetHeight());
    ;
}

TEST(AppGuiConfigTest, AppMinSizeNegative1)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appMinSize" : [ 300 ]})");
    EXPECT_EQ(kAppMinSizeW, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(kAppMinSizeH, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizeNegative3)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appMinSize" : [ 250, 300, 400 ]})");
    EXPECT_EQ(kAppMinSizeW, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(kAppMinSizeH, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizeException)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appMinSize" : [ 250, "exception" ]})");
    EXPECT_EQ(kAppMinSizeW, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(kAppMinSizeH, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartPositionEmpty)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr("{}");
    EXPECT_EQ(wxDefaultPosition.x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(wxDefaultPosition.y, cfg.GetAppStartPosition().y);
}

TEST(AppGuiConfigTest, AppStartPositionPositive)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appStartPosition" : [ 250, 300 ]})");
    EXPECT_EQ(250, cfg.GetAppStartPosition().x);
    EXPECT_EQ(300, cfg.GetAppStartPosition().y);
    ;
}

TEST(AppGuiConfigTest, AppStartPositionNegative1)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appStartPosition" : [ 300 ]})");
    EXPECT_EQ(wxDefaultPosition.x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(wxDefaultPosition.y, cfg.GetAppStartPosition().y);
}

TEST(AppGuiConfigTest, AppStartPositionNegative3)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appStartPosition" : [ 250, 300, 400 ]})");
    EXPECT_EQ(wxDefaultPosition.x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(wxDefaultPosition.y, cfg.GetAppStartPosition().y);
}

TEST(AppGuiConfigTest, AppStartPositionException)
{
    AppGuiConfig cfg;

    cfg.ReadConfigFromJsonStr(R"({"appStartPosition" : [ 250, "exception" ]})");
    EXPECT_EQ(wxDefaultPosition.x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(wxDefaultPosition.y, cfg.GetAppStartPosition().y);
}
