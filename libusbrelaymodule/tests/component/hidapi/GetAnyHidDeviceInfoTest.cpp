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

#include "hidapi.h"

#include "HidapiUtils.h"
#include "cpp-utils/Macros.h"

using namespace nkhlab::usbrelaymodule::impl;

int main(int argc, char const* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    hid_device_info* dev = hid_enumerate(0, 0);

    if (dev)
        std::cout << HidDeviceInfoToStr(dev);
    else
        printf("No USB HID device!\n");

    return 0;
}

/* Example of output:

path:             /dev/hidraw1
vendor_id:        0x413c
product_id:       0x2113
serial_number:
release_number:   264
manufacturer:     (null)
product:          Dell KB216 Wired Keyboard
interface_number: 0

*/
