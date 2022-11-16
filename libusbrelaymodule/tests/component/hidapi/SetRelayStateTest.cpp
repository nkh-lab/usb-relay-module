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
#include <iomanip>
#include <iostream>

#include "hidapi.h"

#include "RelayModuleDcttech.h"
#include "Utils.h"

using namespace nkhlab::usbrelaymodule::impl;
using namespace nkhlab::usbrelaymodule::utils;

int main(int argc, char const* argv[])
{
    int main_ret = EXIT_SUCCESS;

    if (argc < 3)
    {
        std::cout << "Please provide argumnets: <relay-index> <value 0 or 1>\n";
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
                uint8_t relay_idx = static_cast<uint8_t>(std::stoi(argv[1]));
                uint8_t relay_val = std::stoi(argv[2]) == 1 ? RelayModuleDcttech::kCmdRelayOn
                                                            : RelayModuleDcttech::kCmdRelayOff;

                uint8_t data[RelayModuleDcttech::kDataSizeBytes] = {0};
                data[0] = RelayModuleDcttech::kReportIDSet;
                data[1] = relay_val;
                data[2] = relay_idx;

                std::cout << "hid_send_feature_report(" << PrintBytes(data, sizeof(data)) << ") ";
                // int ret = hid_write(handle, data, sizeof(data)); // On Ubuntu it works as well
                int ret = hid_send_feature_report(handle, data, sizeof(data));
                std::cout << "returned " << ret << "\n";
                if (ret != -1)
                {
                    std::cout << PrintBytes(data, sizeof(data)) << "\n";
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

$ ./SetRelayStateTest 1 1
hid_send_feature_report(00 ff 01 00 00 00 00 00 00) returned 9
00 ff 01 00 00 00 00 00 00

*/