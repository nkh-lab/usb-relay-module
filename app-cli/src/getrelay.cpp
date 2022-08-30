#include <iostream>

#include "GetRelayWorker.h"
#include "RelayManager.h"
#include "utils.h"

using namespace nlab;

int main(int argc, char const* argv[])
{
    GetRelayWorker worker(urm::CreateHidapiManagerForDcttechModules());

    std::stringstream out;

    bool ret = worker.Do(argc, argv, out);
    std::cout << out.str();

    return ret == true ? EXIT_SUCCESS : EXIT_FAILURE;
}