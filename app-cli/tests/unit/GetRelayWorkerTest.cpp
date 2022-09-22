/*
 * Copyright (C) 2022 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#include <gtest/gtest.h>

#include "Config.h"
#include "GetRelayWorker.h"
#include "MockRelayManager.h"
#include "MockRelayModule.h"
#include "TextUserInterface.h"
#include "Utils.h"

using namespace nkhlab::usbrelaymodule;
using namespace nkhlab::usbrelaymodule::appcli;
using namespace nkhlab::usbrelaymodule::tests;
using namespace nkhlab::usbrelaymodule::utils;
using namespace nkhlab::usbrelaymodule::config;

using ::testing::Return;
using namespace ::testing;

template <typename T, size_t N>
constexpr size_t arraySize(T (&)[N])
{
    return N;
}

class GetRelayWorkerTest : public ::testing::Test
{
protected:
    const char* kModuleInfo1 =
        "path:             /dev/hidraw4\n"
        "vendor_id:        0x16c0\n"
        "product_id:       0x05df\n"
        "serial_number:\n"
        "release_number:   256\n"
        "manufacturer:     www.dcttech.com\n"
        "product:          USBRelay2\n"
        "interface_number: 0\n";

    const char* kModuleInfo2 =
        "path:             /dev/hidraw5\n"
        "vendor_id:        0x16c0\n"
        "product_id:       0x05df\n"
        "serial_number:\n"
        "release_number:   256\n"
        "manufacturer:     www.dcttech.com\n"
        "product:          USBRelay2\n"
        "interface_number: 0\n";

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

TEST_F(GetRelayWorkerTest, VersionShortArg)
{
    const char* argv[] = {"", "-v"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(
        out,
        Sprintf(TextUserInterface::kVersion, kProjectVerMajor, kProjectVerMinor, kProjectVerPatch));
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, VersionLongArg)
{
    const char* argv[] = {"", "--version"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(
        out,
        Sprintf(TextUserInterface::kVersion, kProjectVerMajor, kProjectVerMinor, kProjectVerPatch));
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, HelpShortArg)
{
    const char* argv[] = {"", "-h"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kGetRelayHelp});
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, HelpLongArg)
{
    const char* argv[] = {"", "--help"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kGetRelayHelp});
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, BadArg)
{
    const char* argv[] = {"", "--h"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, Sprintf(TextUserInterface::kErrorBadArgument, argv[1]));
    EXPECT_FALSE(ret);
}

TEST_F(GetRelayWorkerTest, WrongArgUsage1)
{
    const char* argv[] = {"", "--bla"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kErrorWrongArgumentUsage});
    EXPECT_FALSE(ret);
}

TEST_F(GetRelayWorkerTest, WrongArgUsage2)
{
    const char* argv[] = {"", "--version --help"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kErrorWrongArgumentUsage});
    EXPECT_FALSE(ret);
}

TEST_F(GetRelayWorkerTest, WrongArgUsage3)
{
    const char* argv[] = {"", "-vh"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kErrorWrongArgumentUsage});
    EXPECT_FALSE(ret);
}

TEST_F(GetRelayWorkerTest, NoArgsNoModules)
{
    const char* argv[] = {""};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(1).WillOnce(Return(relay_modules_size0_));
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kNoModules});
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, NoArgsOneModule)
{
    const char* argv[] = {""};
    int argc = arraySize(argv);
    std::string module_name{"module1"};
    std::vector<bool> channels{0, 1};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(1).WillOnce(Return(relay_modules_size1_));
    EXPECT_CALL(*module1_, GetInfo()).Times(1).WillOnce(Return(std::string{kModuleInfo1}));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<0>(module_name), SetArgReferee<1>(channels), Return(true)));
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out;
    std::string expected_channels_out;

    for (size_t i = 0; i < channels.size(); ++i)
    {
        expected_channels_out +=
            Sprintf(TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(channels[i]));
    }

    expected_out = Sprintf(
        TextUserInterface::kGetRelayInfoAndState,
        kModuleInfo1,
        module_name.c_str(),
        expected_channels_out.c_str());

    /* Debug
    std::cout << "=================================================\n";
    std::cout << expected_out;
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_EQ(out, expected_out);
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, NoArgsOneModuleAndFailedGetNameAndChannels)
{
    const char* argv[] = {""};
    int argc = arraySize(argv);
    std::string module_name = Sprintf("< %s >", TextUserInterface::kErrorInaccessible);
    std::vector<bool> channels{};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(1).WillOnce(Return(relay_modules_size1_));
    EXPECT_CALL(*module1_, GetInfo()).Times(1).WillOnce(Return(std::string{kModuleInfo1}));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<0>(module_name), SetArgReferee<1>(channels), Return(false)));
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out;
    std::string expected_channels_out;

    for (size_t i = 0; i < channels.size(); ++i)
    {
        expected_channels_out +=
            Sprintf(TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(channels[i]));
    }

    expected_out = Sprintf(
        TextUserInterface::kGetRelayInfoAndState,
        kModuleInfo1,
        module_name.c_str(),
        expected_channels_out.c_str());

    /* Debug
    std::cout << "=================================================\n";
    std::cout << expected_out;
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_EQ(out, expected_out);
    EXPECT_FALSE(ret);
}

TEST_F(GetRelayWorkerTest, NoArgsTwoModules)
{
    const char* argv[] = {""};
    int argc = arraySize(argv);
    std::string module1_name{"module1"};
    std::vector<bool> module1_channels{0, 1};
    std::string module2_name{"module2"};
    std::vector<bool> module2_channels{0, 1, 0, 1, 0, 1, 0, 1};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(1).WillOnce(Return(relay_modules_size2_));
    EXPECT_CALL(*module1_, GetInfo()).Times(1).WillOnce(Return(std::string{kModuleInfo1}));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module1_name), SetArgReferee<1>(module1_channels), Return(true)));
    EXPECT_CALL(*module2_, GetInfo()).Times(1).WillOnce(Return(std::string{kModuleInfo2}));
    EXPECT_CALL(*module2_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module2_name), SetArgReferee<1>(module2_channels), Return(true)));
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out;
    std::string expected_channels_out;

    for (size_t i = 0; i < module1_channels.size(); ++i)
    {
        expected_channels_out += Sprintf(
            TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(module1_channels[i]));
    }

    expected_out = Sprintf(
        TextUserInterface::kGetRelayInfoAndState,
        kModuleInfo1,
        module1_name.c_str(),
        expected_channels_out.c_str());

    expected_channels_out.clear();

    for (size_t i = 0; i < module2_channels.size(); ++i)
    {
        expected_channels_out += Sprintf(
            TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(module2_channels[i]));
    }

    expected_out += "\n";

    expected_out += Sprintf(
        TextUserInterface::kGetRelayInfoAndState,
        kModuleInfo2,
        module2_name.c_str(),
        expected_channels_out.c_str());

    /* Debug
    std::cout << "=================================================\n";
    std::cout << expected_out;
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_EQ(out, expected_out);
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, RequestExistingModule)
{
    const char* argv[] = {"", "module2"};
    int argc = arraySize(argv);
    std::string module1_name{"module1"};
    std::vector<bool> module1_channels{0, 1};
    std::string module2_name{"module2"};
    std::vector<bool> module2_channels{0, 1, 0, 1, 0, 1, 0, 1};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(1).WillOnce(Return(relay_modules_size2_));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module1_name), SetArgReferee<1>(module1_channels), Return(true)));
    EXPECT_CALL(*module2_, GetInfo()).Times(1).WillOnce(Return(std::string{kModuleInfo2}));
    EXPECT_CALL(*module2_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module2_name), SetArgReferee<1>(module2_channels), Return(true)));
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out;
    std::string expected_channels_out;

    for (size_t i = 0; i < module2_channels.size(); ++i)
    {
        expected_channels_out += Sprintf(
            TextUserInterface::kChannelNameAndState, i + 1, static_cast<int>(module2_channels[i]));
    }

    expected_out += Sprintf(
        TextUserInterface::kGetRelayInfoAndState,
        kModuleInfo2,
        module2_name.c_str(),
        expected_channels_out.c_str());

    /* Debug
    std::cout << "=================================================\n";
    std::cout << expected_out;
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_EQ(out, expected_out);
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, RequestUnexistingModule)
{
    const char* argv[] = {"", "module3"};
    int argc = arraySize(argv);
    std::string module1_name{"module1"};
    std::vector<bool> module1_channels{0, 1};
    std::string module2_name{"module2"};
    std::vector<bool> module2_channels{0, 1, 0, 1, 0, 1, 0, 1};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(1).WillOnce(Return(relay_modules_size2_));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module1_name), SetArgReferee<1>(module1_channels), Return(true)));
    EXPECT_CALL(*module2_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module2_name), SetArgReferee<1>(module2_channels), Return(true)));
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out = Sprintf(TextUserInterface::kErrorNoRequestedModule, "module3");

    /* Debug
    std::cout << "=================================================\n";
    std::cout << expected_out;
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_EQ(out, expected_out);
    EXPECT_FALSE(ret);
}

TEST_F(GetRelayWorkerTest, RequestExistingChannel)
{
    const char* argv[] = {"", "module2_2"};
    int argc = arraySize(argv);
    std::string module1_name{"module1"};
    std::vector<bool> module1_channels{0, 1};
    std::string module2_name{"module2"};
    std::vector<bool> module2_channels{0, 1};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(1).WillOnce(Return(relay_modules_size2_));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module1_name), SetArgReferee<1>(module1_channels), Return(true)));
    EXPECT_CALL(*module2_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module2_name), SetArgReferee<1>(module2_channels), Return(true)));
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out =
        Sprintf(TextUserInterface::kGetChannelState, static_cast<int>(module2_channels[2 - 1]));

    /* Debug
    std::cout << "=================================================\n";
    std::cout << expected_out;
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_EQ(out, expected_out);
    EXPECT_TRUE(ret);
}

TEST_F(GetRelayWorkerTest, RequestNonexistingChannel)
{
    const char* argv[] = {"", "module2_3"};
    int argc = arraySize(argv);
    std::string module1_name{"module1"};
    std::vector<bool> module1_channels{0, 1};
    std::string module2_name{"module2"};
    std::vector<bool> module2_channels{0, 1};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(1).WillOnce(Return(relay_modules_size2_));
    EXPECT_CALL(*module1_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module1_name), SetArgReferee<1>(module1_channels), Return(true)));
    EXPECT_CALL(*module2_, GetNameAndChannels(_, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(module2_name), SetArgReferee<1>(module2_channels), Return(true)));
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out = Sprintf(TextUserInterface::kErrorNoRequestedChannel, 3, "module2");

    /* Debug
    std::cout << "=================================================\n";
    std::cout << expected_out;
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_EQ(out, expected_out);
    EXPECT_FALSE(ret);
}

TEST_F(GetRelayWorkerTest, WrongArgUsage)
{
    const char* argv[] = {"", "module1_1=1"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    GetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out = TextUserInterface::kErrorWrongArgumentUsage;

    /* Debug
    std::cout << "=================================================\n";
    std::cout << expected_out;
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_EQ(out, expected_out);
    EXPECT_FALSE(ret);
}
