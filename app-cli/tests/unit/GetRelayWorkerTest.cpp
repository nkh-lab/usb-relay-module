#include <gtest/gtest.h>

#include "GetRelayWorker.h"
#include "TextUserInterface.h"
#include "utils.h"

using namespace nlab;

template <typename T, size_t N>
constexpr size_t arraySize(T (&)[N])
{
    return N;
}

TEST(GetRelayWorkerTest, VersionShortArg)
{
    const char* argv[] = {"", "-v"};
    int argc = arraySize(argv);

    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.CheckArgsAndAnswer(argc, argv, out);

    EXPECT_EQ(out, utils::Sprintf(TextUserInterface::kVersion, 0, 0, 1));
}

TEST(GetRelayWorkerTest, VersionLongArg)
{
    const char* argv[] = {"", "--version"};
    int argc = arraySize(argv);

    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.CheckArgsAndAnswer(argc, argv, out);

    EXPECT_EQ(out, utils::Sprintf(TextUserInterface::kVersion, 0, 0, 1));
}

TEST(GetRelayWorkerTest, HelpShortArg)
{
    const char* argv[] = {"", "-h"};
    int argc = arraySize(argv);

    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.CheckArgsAndAnswer(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kHelp});
}

TEST(GetRelayWorkerTest, HelpLongArg)
{
    const char* argv[] = {"", "--help"};
    int argc = arraySize(argv);

    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.CheckArgsAndAnswer(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kHelp});
}

TEST(GetRelayWorkerTest, BadArg)
{
    const char* argv[] = {"", "--h"};
    int argc = arraySize(argv);

    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.CheckArgsAndAnswer(argc, argv, out);

    EXPECT_EQ(out, utils::Sprintf(TextUserInterface::kBadArgument, argv[1]));
}

TEST(GetRelayWorkerTest, WrongArgUsage1)
{
    const char* argv[] = {"", "--bla"};
    int argc = arraySize(argv);

    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.CheckArgsAndAnswer(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kWrongArgumentUsage});
}

TEST(GetRelayWorkerTest, WrongArgUsage2)
{
    const char* argv[] = {"", "--version --help"};
    int argc = arraySize(argv);

    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.CheckArgsAndAnswer(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kWrongArgumentUsage});
}

TEST(GetRelayWorkerTest, WrongArgUsage3)
{
    const char* argv[] = {"", "-vh"};
    int argc = arraySize(argv);

    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.CheckArgsAndAnswer(argc, argv, out);

    EXPECT_EQ(out, std::string{TextUserInterface::kWrongArgumentUsage});
}