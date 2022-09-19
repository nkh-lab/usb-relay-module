#include <iostream>

#include "GetRelayWorker.h"
#include "RelayManager.h"
#include "Utils.h"

using namespace nkhlab::usbrelaymodule;
using namespace nkhlab::usbrelaymodule::appcli;

int main(int argc, char const* argv[])
{
    GetRelayWorker worker(CreateHidapiManagerForDcttechModules());

    std::string out;

    bool ret = worker.Run(argc, argv, out);
    std::cout << out;

    return ret == true ? EXIT_SUCCESS : EXIT_FAILURE;
}