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
#include "MockRelayManager.h"
#include "MockRelayModule.h"
#include "SetRelayWorker.h"
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

class SetRelayWorkerTest : public ::testing::Test
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

TEST_F(SetRelayWorkerTest, VersionShortArg)
{
    const char* argv[] = {"", "-v"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(
        out,
        Sprintf(TextUserInterface::kVersion, kProjectVerMajor, kProjectVerMinor, kProjectVerPatch));
    EXPECT_TRUE(ret);
}

TEST_F(SetRelayWorkerTest, VersionLongArg)
{
    const char* argv[] = {"", "--version"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(
        out,
        Sprintf(TextUserInterface::kVersion, kProjectVerMajor, kProjectVerMinor, kProjectVerPatch));
    EXPECT_TRUE(ret);
}

TEST_F(SetRelayWorkerTest, HelpShortArg)
{
    const char* argv[] = {"", "-h"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kSetRelayHelp});
    EXPECT_TRUE(ret);
}

TEST_F(SetRelayWorkerTest, HelpLongArg)
{
    const char* argv[] = {"", "--help"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kSetRelayHelp});
    EXPECT_TRUE(ret);
}

TEST_F(SetRelayWorkerTest, BadArg)
{
    const char* argv[] = {"", "--h"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, Sprintf(TextUserInterface::kErrorBadArgument, argv[1]));
    EXPECT_FALSE(ret);
}

TEST_F(SetRelayWorkerTest, WrongArgUsage1)
{
    const char* argv[] = {"", "--bla"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kErrorWrongArgumentUsage});
    EXPECT_FALSE(ret);
}

TEST_F(SetRelayWorkerTest, WrongArgUsage2)
{
    const char* argv[] = {"", "--version --help"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kErrorWrongArgumentUsage});
    EXPECT_FALSE(ret);
}

TEST_F(SetRelayWorkerTest, WrongArgUsage3)
{
    const char* argv[] = {"", "-vh"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kErrorWrongArgumentUsage});
    EXPECT_FALSE(ret);
}

TEST_F(SetRelayWorkerTest, NoArgsNoModules)
{
    const char* argv[] = {""};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kErrorWrongArgumentUsage});
    EXPECT_FALSE(ret);
}

TEST_F(SetRelayWorkerTest, SetExistingChannelToValidValue)
{
    const char* argv[] = {"", "module2_1=0"};
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
    EXPECT_CALL(*module2_, SetChannel(1, false)).Times(1).WillOnce(Return(true));
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    /* Debug
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_TRUE(out.empty());
    EXPECT_TRUE(ret);
}

TEST_F(SetRelayWorkerTest, SetExistingChannelToUnvalidValue)
{
    const char* argv[] = {"", "module2_1=3"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    std::string expected_out{std::string{TextUserInterface::kErrorWrongArgumentUsage}};

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

TEST_F(SetRelayWorkerTest, SetUnexistingChannelToValidValue)
{
    const char* argv[] = {"", "module2_3=0"};
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

    SetRelayWorker worker(std::move(relay_manager_));

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

TEST_F(SetRelayWorkerTest, SetChannel0ToValidValue)
{
    const char* argv[] = {"", "module2_0=0"};
    int argc = arraySize(argv);
    std::string module1_name{"module1"};
    std::vector<bool> module1_channels{0, 1};
    std::string module2_name{"module2"};
    std::vector<bool> module2_channels{0, 1};

    // Mocking
    EXPECT_CALL(*relay_manager_, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager_));

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

TEST_F(SetRelayWorkerTest, RenameModule)
{
    const char* argv[] = {"", "module2=module2_new"};
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
    EXPECT_CALL(*module2_, SetName("module2_new")).Times(1).WillOnce(Return(true));
    //========

    SetRelayWorker worker(std::move(relay_manager_));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    /* Debug
    std::cout << "=================================================\n";
    std::cout << out;
    std::cout << "=================================================\n";
    */

    EXPECT_TRUE(out.empty());
    EXPECT_TRUE(ret);
}