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

TEST(AppGuiConfigTest, AliasSettingsNoConfig)
{
    AppGuiConfig cfg;

    EXPECT_GE(cfg.GetAliasPages().size(), 0);
}

TEST(AppGuiConfigTest, AliasSettingsGoodConfig)
{
    AppGuiConfig cfg;
    // clang-format off
    std::string js = StringHelper::Sprintf(R"(
{
   "%s" : {
      "green" : [ 0, 255, 0 ],
      "red" : [ 255, 0, 0 ]
   },
   "%s" : [
      {
         "%s" : [
            {
               "R1_3" : [ "R1_3 Alias", "State0", "green", "State1", "red" ]
            },
            {
               "R1_1" : [ "R1_1 Alias", "State0", "green", "State1", "red" ]
            },
            {
               "R1_2" : [ "R1_2 Alias", "State0", "green", "State1", "red" ]
            }
         ],
         "%s" : "Alias Example"
      }
   ]
}
    )", kJsonKeyAliasColors, kJsonKeyAliasPages, kJsonKeyAliasChannels, kJsonKeyAliasPageName);
    // clang-format on

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_EQ(cfg.GetAliasPages().size(), 1);
    EXPECT_EQ(cfg.GetAliasPages()[0].channels.size(), 3);
    EXPECT_STREQ(cfg.GetAliasPages()[0].channels[0].second.text.c_str(), "R1_3 Alias");
    EXPECT_STREQ(cfg.GetAliasPages()[0].channels[1].second.text.c_str(), "R1_1 Alias");
    EXPECT_STREQ(cfg.GetAliasPages()[0].channels[2].second.text.c_str(), "R1_2 Alias");
}

TEST(AppGuiConfigTest, AliasSettingsEmpty)
{
    AppGuiConfig cfg;

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr("{}"));
    EXPECT_EQ(cfg.GetAliasPages().size(), 0);
}

TEST(AppGuiConfigTest, AliasSettingsEmptyColors)
{
    AppGuiConfig cfg;
    // clang-format off
    std::string js = StringHelper::Sprintf(R"(
{
   "%s" : {},
   "%s" : [
      {
         "%s" : [
            {
               "R1_3" : [ "R1_3 Alias", "State0", "green", "State1", "red" ]
            }
         ],
         "%s" : "Alias Example"
      }
   ]
}
    )", kJsonKeyAliasColors, kJsonKeyAliasPages, kJsonKeyAliasChannels, kJsonKeyAliasPageName);
    // clang-format on

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_TRUE(cfg.GetAliasPages().empty());
}

TEST(AppGuiConfigTest, AliasSettingsBadColorFormat)
{
    AppGuiConfig cfg;
    // clang-format off
    std::string js = StringHelper::Sprintf(R"(
{
   "%s" : {
      "green" : [ 0, 255 ],
      "red" : [ 255, 0, "exception" ]
   },
   "%s" : [
      {
         "%s" : [
            {
               "R1_3" : [ "R1_3 Alias", "State0", "green", "State1", "red" ]
            }
         ],
         "%s" : "Alias Example"
      }
   ]
}
    )", kJsonKeyAliasColors, kJsonKeyAliasPages, kJsonKeyAliasChannels, kJsonKeyAliasPageName);
    // clang-format on

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_TRUE(cfg.GetAliasPages().empty());
}

TEST(AppGuiConfigTest, AliasSettingsNoAliasPageName)
{
    AppGuiConfig cfg;
    // clang-format off
    std::string js = StringHelper::Sprintf(R"(
{
   "%s" : {
      "green" : [ 0, 255, 0 ],
      "red" : [ 255, 0, 0 ]
   },
   "%s" : [
      {
         "%s" : [
            {
               "R1_3" : [ "R1_3 Alias", "State0", "green", "State1", "red" ]
            }
         ]
      }
   ]
}
    )", kJsonKeyAliasColors, kJsonKeyAliasPages, kJsonKeyAliasChannels);
    // clang-format on

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_TRUE(cfg.GetAliasPages().empty());
}

TEST(AppGuiConfigTest, AliasSettingsWrongChannelFormat)
{
    AppGuiConfig cfg;
    // clang-format off
    std::string js = StringHelper::Sprintf(R"(
{
   "%s" : {
      "green" : [ 0, 255, 0 ],
      "red" : [ 255, 0, 0 ]
   },
   "%s" : [
      {
         "%s" : [
            {
                // Not full
               "R1_3" : [ "R1_3 Alias", "State0", "green", "State1" ]
            },
            {
                // Over full
               "R1_1" : [ "R1_1 Alias", "State0", "green", "State1", "red", "red" ]
            },
            {
                // Wrong type
               "R1_2" : [ "R1_2 Alias", "State0", "green", "State1", true ]
            }
            ,
            {
                // Nonexistent colors
               "R1_4" : [ "R1_2 Alias", "State0", "white", "State1", "black" ]
            },
            {
                // Empty
            }
         ],
         "%s" : "Alias Example"
      }
   ]
}
    )", kJsonKeyAliasColors, kJsonKeyAliasPages, kJsonKeyAliasChannels, kJsonKeyAliasPageName);
    // clang-format on

    EXPECT_TRUE(cfg.ReadConfigFromJsonStr(js));
    EXPECT_TRUE(cfg.GetAliasPages().empty());
}
