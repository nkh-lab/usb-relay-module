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

#include "HidapiUtils.h"

#include "cpp-utils/StringHelper.h"

#include <iomanip>
#include <sstream>

using namespace nkhlab::cpputils;

namespace {
constexpr char kNullText[] = "(null)";
}

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

std::string HidDeviceInfoToStr(hid_device_info* dev)
{
    std::stringstream ss;

    ss << "path:             " << dev->path << "\n";
    ss << std::hex;
    ss << "vendor_id:        0x" << std::setfill('0') << std::setw(4) << dev->vendor_id << "\n";
    ss << "product_id:       0x" << std::setfill('0') << std::setw(4) << dev->product_id << "\n";
    ss << std::dec; // back to dec
    ss << "serial_number:    "
       << (dev->serial_number ? StringHelper::WstrToStr(dev->serial_number) : kNullText) << "\n";
    ss << "release_number:   " << dev->release_number << "\n";
    ss << "manufacturer:     "
       << (dev->manufacturer_string ? StringHelper::WstrToStr(dev->manufacturer_string) : kNullText)
       << "\n";
    ss << "product:          "
       << (dev->product_string ? StringHelper::WstrToStr(dev->product_string) : kNullText) << "\n";
    ss << "interface_number: " << dev->interface_number << "\n";

    return ss.str();
}

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab