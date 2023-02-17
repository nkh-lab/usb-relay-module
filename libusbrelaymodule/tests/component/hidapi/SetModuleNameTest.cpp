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

#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "hidapi.h"

#include "RelayModuleDcttech.h"
#include "StringHelper.h"

using namespace nkhlab::usbrelaymodule::impl;
using namespace nkhlab::usbrelaymodule::utils;

int main(int argc, char const* argv[])
{
    int main_ret = EXIT_SUCCESS;

    if (argc < 2)
    {
        std::cout << "Please provide argumnet: <new module name, max 5 chars>\n";
        main_ret = EXIT_FAILURE;
    }
    else
    {
        hid_device_info* dev =
            hid_enumerate(RelayModuleDcttech::kUsbVendorId, RelayModuleDcttech::kUsbProductId);
        if (dev)
        {
            hid_device* handle = hid_open_path(dev->path);
            if (handle)
            {
                const char* new_module_name = argv[1];
                size_t new_module_name_size = std::strlen(new_module_name);
                size_t name_size_to_copy = new_module_name_size < RelayModuleDcttech::kNameSizeBytes
                                               ? new_module_name_size
                                               : RelayModuleDcttech::kNameSizeBytes;

                uint8_t data[RelayModuleDcttech::kDataSizeBytes] = {0};
                data[0] = RelayModuleDcttech::kReportIDSet;
                data[1] = RelayModuleDcttech::kCmdSetModuleName;
                std::copy(new_module_name, new_module_name + name_size_to_copy, &data[2]);

                std::cout << "hid_send_feature_report("
                          << StringHelper::PrintBytes(data, sizeof(data)) << ") ";
                // int ret = hid_write(handle, data, sizeof(data)); // On Ubuntu it works as well
                int ret = hid_send_feature_report(handle, data, sizeof(data));
                std::cout << "returned " << ret << "\n";
                if (ret != -1)
                {
                    std::cout << StringHelper::PrintBytes(data, sizeof(data)) << "\n";
                }
                else
                    main_ret = EXIT_FAILURE;
            }
            else
                printf("hid_open_path(%s) returned -1\n", dev->path);

            hid_close(handle);
        }
    }

    return main_ret;
}

/* Example of output:

$ ./SetModuleNameTest R1
hid_send_feature_report(00 fa 52 31 00 00 00 00 00) returned 9
00 fa 52 31 00 00 00 00 00

*/