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

#include "simu/SimuJsonHelper.h"

using namespace nkhlab::usbrelaymodule::impl::simu;

TEST(SimuJsonHelperTest, BuildJsonTemplate)
{
    Json::Value jroot = SimuJsonHelper::BuildJsonTemplate();
    auto modules = SimuJsonHelper::JsonToModules(jroot);

    EXPECT_EQ(modules.size(), kJsonTemplateModuleSize);

    for (const auto& m : modules)
    {
        EXPECT_EQ(m.second.size(), kJsonTemplateChannelSize);
    }
}

TEST(SimuJsonHelperTest, ChangeModuleNameInJson)
{
    Json::Reader jreader;
    Json::Value jroot;

    // clang-format off
    std::string js = R"(
{
    "R1" : [ 0, 0 ],
    "R2" : [ 0, 0 ]
}
    )";
    // clang-format on

    bool parsed = jreader.parse(js, jroot);

    EXPECT_TRUE(parsed);

    if (parsed)
    {
        auto parsed_modules = SimuJsonHelper::JsonToModules(jroot);

        EXPECT_TRUE(SimuJsonHelper::ChangeModuleNameInJson(jroot, "R1", "R1new"));

        EXPECT_FALSE(SimuJsonHelper::ChangeModuleNameInJson(jroot, "R3", "R3new"));

        auto modules = SimuJsonHelper::JsonToModules(jroot);

        EXPECT_EQ(modules.size(), 2);
        EXPECT_TRUE(modules.count("R1new"));
    }
}

TEST(SimuJsonHelperTest, SetChannelStateInJson)
{
    Json::Reader jreader;
    Json::Value jroot;

    // clang-format off
    std::string js = R"(
{
    "R1" : [ 0, 0 ],
    "R2" : [ 0, 0 ]
}
    )";
    // clang-format on

    bool parsed = jreader.parse(js, jroot);

    EXPECT_TRUE(parsed);

    if (parsed)
    {
        auto parsed_modules = SimuJsonHelper::JsonToModules(jroot);

        EXPECT_FALSE(parsed_modules["R1"][0]);
        EXPECT_FALSE(parsed_modules["R1"][1]);

        EXPECT_TRUE(SimuJsonHelper::SetChannelStateInJson(jroot, "R1", 1, true));
        EXPECT_TRUE(SimuJsonHelper::SetChannelStateInJson(jroot, "R1", 2, true));
        EXPECT_FALSE(SimuJsonHelper::SetChannelStateInJson(jroot, "R1", 3, true));

        parsed_modules = SimuJsonHelper::JsonToModules(jroot);

        EXPECT_TRUE(parsed_modules["R1"][0]);
        EXPECT_TRUE(parsed_modules["R1"][1]);

        EXPECT_TRUE(SimuJsonHelper::SetChannelStateInJson(jroot, "R1", 1, false));
        EXPECT_TRUE(SimuJsonHelper::SetChannelStateInJson(jroot, "R1", 2, false));

        parsed_modules = SimuJsonHelper::JsonToModules(jroot);

        EXPECT_FALSE(parsed_modules["R1"][0]);
        EXPECT_FALSE(parsed_modules["R1"][1]);
    }
}