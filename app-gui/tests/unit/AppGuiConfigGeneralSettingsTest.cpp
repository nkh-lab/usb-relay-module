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
#include "cpp-utils/StringHelper.h"

using namespace nkhlab::usbrelaymodule::appgui;
using namespace nkhlab::cpputils;

TEST(AppGuiConfigTest, HideAllChannelsPageEmpty)
{
    AppGuiConfig cfg;

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr("{}"));
    EXPECT_FALSE(cfg.IsHideAllChannelsPage());
}

TEST(AppGuiConfigTest, HideAllChannelsPageFalse)
{
    AppGuiConfig cfg;
    std::string js = StringHelper::Sprintf(R"({"%s" : false})", kJsonKeyHideAllChannelsPage);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_FALSE(cfg.IsHideAllChannelsPage());
}

TEST(AppGuiConfigTest, HideAllChannelsPageTrue)
{
    AppGuiConfig cfg;
    std::string js = StringHelper::Sprintf(R"({"%s" : true})", kJsonKeyHideAllChannelsPage);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_TRUE(cfg.IsHideAllChannelsPage());
}

TEST(AppGuiConfigTest, HideAllChannelsPageException)
{
    AppGuiConfig cfg;
    std::string js = StringHelper::Sprintf(R"({"%s" : "exception"})", kJsonKeyHideAllChannelsPage);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_FALSE(cfg.IsHideAllChannelsPage());
}

TEST(AppGuiConfigTest, AppStartSizeEmpty)
{
    AppGuiConfig cfg;

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr("{}"));
    EXPECT_EQ(wxDefaultSize.GetWidth(), cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(wxDefaultSize.GetHeight(), cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartSizePositive)
{
    AppGuiConfig cfg;
    int w = 250, h = 300;
    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d, %d ]})", kJsonKeyAppStartSize, w, h);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_EQ(w, cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(h, cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartSizeNegative1)
{
    AppGuiConfig cfg;
    int w = 250;

    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d ]})", kJsonKeyAppStartSize, w);
    EXPECT_EQ(wxDefaultSize.GetWidth(), cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(wxDefaultSize.GetHeight(), cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartSizeNegative3)
{
    AppGuiConfig cfg;
    int w = 250, h = 300, z = 400;

    std::string js =
        StringHelper::Sprintf(R"({"%s" : [ %d, %d, %d ]})", kJsonKeyAppStartSize, w, h, z);
    EXPECT_EQ(wxDefaultSize.GetWidth(), cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(wxDefaultSize.GetHeight(), cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartSizeException)
{
    AppGuiConfig cfg;
    int w = 250;

    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d, "exception" ]})", kJsonKeyAppStartSize, w);
    EXPECT_EQ(wxDefaultSize.GetWidth(), cfg.GetAppStartSize().GetWidth());
    EXPECT_EQ(wxDefaultSize.GetHeight(), cfg.GetAppStartSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizeEmpty)
{
    AppGuiConfig cfg;

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr("{}"));
    EXPECT_EQ(kAppMinSizeW, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(kAppMinSizeH, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizePositive)
{
    AppGuiConfig cfg;
    int w = 250, h = 300;
    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d, %d ]})", kJsonKeyAppMinSize, w, h);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_EQ(250, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(300, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizeNegative1)
{
    AppGuiConfig cfg;
    int w = 250;
    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d ]})", kJsonKeyAppMinSize, w);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_EQ(kAppMinSizeW, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(kAppMinSizeH, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizeNegative3)
{
    AppGuiConfig cfg;
    int w = 250, h = 300, z = 400;

    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d, %d, %d ]})", kJsonKeyAppMinSize, w, h, z);
    EXPECT_EQ(kAppMinSizeW, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(kAppMinSizeH, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppMinSizeException)
{
    AppGuiConfig cfg;
    int w = 250;

    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d, "exception" ]})", kJsonKeyAppMinSize, w);
    EXPECT_EQ(kAppMinSizeW, cfg.GetAppMinSize().GetWidth());
    EXPECT_EQ(kAppMinSizeH, cfg.GetAppMinSize().GetHeight());
}

TEST(AppGuiConfigTest, AppStartPositionEmpty)
{
    AppGuiConfig cfg;

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr("{}"));
    EXPECT_EQ(wxDefaultPosition.x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(wxDefaultPosition.y, cfg.GetAppStartPosition().y);
}

TEST(AppGuiConfigTest, AppStartPositionPositive)
{
    AppGuiConfig cfg;
    int x = 250, y = 300;
    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d, %d ]})", kJsonKeyAppStartPos, x, y);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_EQ(x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(y, cfg.GetAppStartPosition().y);
}

TEST(AppGuiConfigTest, AppStartPositionNegative1)
{
    AppGuiConfig cfg;
    int x = 250;
    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d ]})", kJsonKeyAppStartPos, x);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_EQ(wxDefaultPosition.x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(wxDefaultPosition.y, cfg.GetAppStartPosition().y);
}

TEST(AppGuiConfigTest, AppStartPositionNegative3)
{
    AppGuiConfig cfg;
    int x = 250, y = 300, z = 400;
    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d, %d, %d ]})", kJsonKeyAppStartPos, x, y, z);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_EQ(wxDefaultPosition.x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(wxDefaultPosition.y, cfg.GetAppStartPosition().y);
}

TEST(AppGuiConfigTest, AppStartPositionException)
{
    AppGuiConfig cfg;
    int x = 250;
    std::string js = StringHelper::Sprintf(R"({"%s" : [ %d, "exception" ]})", kJsonKeyAppStartPos, x);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_EQ(wxDefaultPosition.x, cfg.GetAppStartPosition().x);
    EXPECT_EQ(wxDefaultPosition.y, cfg.GetAppStartPosition().y);
}

TEST(AppGuiConfigTest, AppStayOnTopEmpty)
{
    AppGuiConfig cfg;

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr("{}"));
    EXPECT_FALSE(cfg.IsAppStayOnTop());
}

TEST(AppGuiConfigTest, AppStayOnTopFalse)
{
    AppGuiConfig cfg;
    std::string js = StringHelper::Sprintf(R"({"%s" : false})", kJsonKeyAppStayOnTop);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_FALSE(cfg.IsAppStayOnTop());
}

TEST(AppGuiConfigTest, AppStayOnTopTrue)
{
    AppGuiConfig cfg;
    std::string js = StringHelper::Sprintf(R"({"%s" : true})", kJsonKeyAppStayOnTop);

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_TRUE(cfg.IsAppStayOnTop());
}