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

#include <iostream>

#include "GetRelayWorker.h"
#include "RelayManager.h"
#include "Utils.h"

using namespace nkhlab::usbrelaymodule;
using namespace nkhlab::usbrelaymodule::appcli;

int main(int argc, char const* argv[])
{
#ifdef URM_SIMU
    std::string path = argv[0];
    std::size_t found = path.find_last_of("/\\") + 1;
    path = path.substr(0, found);
    GetRelayWorker worker(CreateSimuManager(path));
#else
    GetRelayWorker worker(CreateHidapiManagerForDcttechModules());
#endif
    std::string out;

    bool ret = worker.Run(argc, argv, out);
    std::cout << out;

    return ret == true ? EXIT_SUCCESS : EXIT_FAILURE;
}