#include <iostream>

#include "RelayManager.h"
#include "SetRelayWorker.h"
#include "utils.h"

using namespace nlab;

int main(int argc, char const* argv[])
{
    SetRelayWorker worker(nlab::CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.Run(argc, argv, out);
    std::cout << out;

    return ret == true ? EXIT_SUCCESS : EXIT_FAILURE;
}