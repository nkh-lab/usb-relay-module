#include <iostream>

#include "GetRelayWorker.h"
#include "RelayManager.h"
#include "utils.h"

using namespace nlab;

int main(int argc, char const* argv[])
{
    GetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.GetRelayWorker::CheckArgsAndAnswer(argc, argv, out);
    std::cout << out;

    return ret == true ? EXIT_SUCCESS : EXIT_FAILURE;
}