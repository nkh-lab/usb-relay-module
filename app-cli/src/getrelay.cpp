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
#include "cpp-utils/FileHelper.h"

using namespace nkhlab::usbrelaymodule;
using namespace nkhlab::usbrelaymodule::appcli;
using namespace nkhlab::cpputils;

int main(int argc, const char* argv[])
{
#ifdef URM_SIMU
    std::string app_path = FileHelper::GetDir(argv[0]);
    GetRelayWorker worker(CreateSimuManager(app_path));
#else
    GetRelayWorker worker(CreateHidapiManagerForDcttechModules());
#endif
    std::string out;

    bool ret = worker.Run(argc, argv, out);
    std::cout << out;

    return ret == true ? EXIT_SUCCESS : EXIT_FAILURE;
}