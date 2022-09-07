#include <gtest/gtest.h>

#include "MockRelayManager.h"
#include "MockRelayModule.h"
#include "SetRelayWorker.h"
#include "TextUserInterface.h"
#include "utils.h"

using namespace nlab;

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
        relay_manager = std::make_unique<MockRelayManager>();
        module1 = std::make_shared<MockRelayModule>();
        module2 = std::make_shared<MockRelayModule>();

        relay_modules_size1.push_back(module1);

        relay_modules_size2.push_back(module1);
        relay_modules_size2.push_back(module2);
    }

    // void TearDown() override {}

    std::unique_ptr<MockRelayManager> relay_manager;
    IRelayModulePtrs relay_modules_size0;
    IRelayModulePtrs relay_modules_size1;
    IRelayModulePtrs relay_modules_size2;
    std::shared_ptr<MockRelayModule> module1;
    std::shared_ptr<MockRelayModule> module2;

    // relay_modules.push_back(module1);
};

TEST_F(SetRelayWorkerTest, VersionShortArg)
{
    const char* argv[] = {"", "-v"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, utils::Sprintf(TextUserInterface::kVersion, 0, 0, 1));
}

TEST_F(SetRelayWorkerTest, VersionLongArg)
{
    const char* argv[] = {"", "--version"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, utils::Sprintf(TextUserInterface::kVersion, 0, 0, 1));
}

TEST_F(SetRelayWorkerTest, HelpShortArg)
{
    const char* argv[] = {"", "-h"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kSetRelayHelp});
}

TEST_F(SetRelayWorkerTest, HelpLongArg)
{
    const char* argv[] = {"", "--help"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kSetRelayHelp});
}

TEST_F(SetRelayWorkerTest, BadArg)
{
    const char* argv[] = {"", "--h"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, utils::Sprintf(TextUserInterface::kBadArgument, argv[1]));
}

TEST_F(SetRelayWorkerTest, WrongArgUsage1)
{
    const char* argv[] = {"", "--bla"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kWrongArgumentUsage});
}

TEST_F(SetRelayWorkerTest, WrongArgUsage2)
{
    const char* argv[] = {"", "--version --help"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kWrongArgumentUsage});
}

TEST_F(SetRelayWorkerTest, WrongArgUsage3)
{
    const char* argv[] = {"", "-vh"};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kWrongArgumentUsage});
}

TEST_F(SetRelayWorkerTest, NoArgsNoModules)
{
    const char* argv[] = {""};
    int argc = arraySize(argv);

    // Mocking
    EXPECT_CALL(*relay_manager, GetModules()).Times(0);
    //========

    SetRelayWorker worker(std::move(relay_manager));

    std::string out;

    bool ret = worker.Run(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kWrongArgumentUsage});
}
