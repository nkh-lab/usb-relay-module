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

#include "MockRelayManager.h"
#include "MockRelayModule.h"
#include "RelayManagerHelper.h"

using namespace nkhlab::usbrelaymodule;
using namespace nkhlab::usbrelaymodule::tests;

using ::testing::Return;
using namespace ::testing;

class RelayManagerHelperTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        relay_manager_ = std::make_unique<MockRelayManager>();
        module1_ = std::make_shared<MockRelayModule>();
        module2_ = std::make_shared<MockRelayModule>();

        relay_modules_size1_.push_back(module1_);

        relay_modules_size2_.push_back(module1_);
        relay_modules_size2_.push_back(module2_);
    }

    // void TearDown() override {}

    std::unique_ptr<MockRelayManager> relay_manager_;
    IRelayModulePtrs relay_modules_size0_;
    IRelayModulePtrs relay_modules_size1_;
    IRelayModulePtrs relay_modules_size2_;
    std::shared_ptr<MockRelayModule> module1_;
    std::shared_ptr<MockRelayModule> module2_;
};

TEST_F(RelayManagerHelperTest, SetChannel)
{
    std::string module1_name{"R1"};
    std::vector<bool> module1_channels{0, 0};
    std::string module2_name{"R2"};
    std::vector<bool> module2_channels{0, 0};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).WillRepeatedly(Return(relay_modules_size2_));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .WillRepeatedly(DoAll(
            SetArgReferee<0>(module1_name), SetArgReferee<1>(module1_channels), Return(true)));
    EXPECT_CALL(*module2_, GetNameAndChannels(_, _))
        .WillRepeatedly(DoAll(
            SetArgReferee<0>(module2_name), SetArgReferee<1>(module2_channels), Return(true)));

    EXPECT_CALL(*module2_, SetChannel(0, true)).Times(2).WillOnce(Return(true)).WillOnce(Return(false));
    //========

    EXPECT_EQ(
        RelayManagerHelper::SetChannel(relay_manager_.get(), "R2_1", true),
        RelayManagerHelper::SetChannelResult::kOk);
    EXPECT_EQ(
        RelayManagerHelper::SetChannel(relay_manager_.get(), "R3_1", true),
        RelayManagerHelper::SetChannelResult::kNoRequestedModule);
    EXPECT_EQ(
        RelayManagerHelper::SetChannel(relay_manager_.get(), "R2_3", true),
        RelayManagerHelper::SetChannelResult::kNoRequestedChannel);
    EXPECT_EQ(
        RelayManagerHelper::SetChannel(relay_manager_.get(), "R2_1", true),
        RelayManagerHelper::SetChannelResult::kSetChannelError);
}

TEST_F(RelayManagerHelperTest, SplitChannelName)
{
    std::string module;
    int channel;

    RelayManagerHelper::SplitChannelName("R2_1", module, channel);
    EXPECT_STREQ(module.c_str(), "R2");
    EXPECT_EQ(channel, 1);

    RelayManagerHelper::SplitChannelName("R2", module, channel);
    EXPECT_STREQ(module.c_str(), "R2");
    EXPECT_EQ(channel, -1);
}

TEST_F(RelayManagerHelperTest, SplitChannelName_UnderscoreInName)
{
    std::string module;
    int channel;

    RelayManagerHelper::SplitChannelName("R_T_1", module, channel);
    EXPECT_STREQ(module.c_str(), "R_T");
    EXPECT_EQ(channel, 1);

    RelayManagerHelper::SplitChannelName("R_T", module, channel);
    EXPECT_STREQ(module.c_str(), "R_T");
    EXPECT_EQ(channel, -1);
}

TEST_F(RelayManagerHelperTest, GetAllChannels)
{
    std::string module1_name{"R1"};
    std::vector<bool> module1_channels{0, 1};
    std::string module2_name{"R2"};
    std::vector<bool> module2_channels{0, 1};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).WillRepeatedly(Return(relay_modules_size2_));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .WillRepeatedly(DoAll(
            SetArgReferee<0>(module1_name), SetArgReferee<1>(module1_channels), Return(true)));
    EXPECT_CALL(*module2_, GetNameAndChannels(_, _))
        .WillRepeatedly(DoAll(
            SetArgReferee<0>(module2_name), SetArgReferee<1>(module2_channels), Return(true)));
    //========

    auto channels = RelayManagerHelper::GetAllChannels(relay_manager_.get());

    EXPECT_EQ(channels.size(), 4);

    EXPECT_FALSE(channels["R1_1"]);
    EXPECT_TRUE(channels["R1_2"]);
    EXPECT_FALSE(channels["R2_1"]);
    EXPECT_TRUE(channels["R2_2"]);
}

TEST_F(RelayManagerHelperTest, GetAllChannelsEmpty)
{
    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).WillRepeatedly(Return(relay_modules_size0_));
    //========

    auto channels = RelayManagerHelper::GetAllChannels(relay_manager_.get());

    EXPECT_EQ(channels.size(), 0);
}
