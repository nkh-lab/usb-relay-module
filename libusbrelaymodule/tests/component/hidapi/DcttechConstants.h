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

#pragma once

namespace nkhlab {
namespace usbrelaymodule {
namespace tests {
namespace hidapi {
namespace dcttech {

constexpr uint16_t kUsbVendorId = 0x16c0;
constexpr uint16_t kUsbProductId = 0x05df;

constexpr size_t kDataSizeBytes = 9;
constexpr size_t kNameSizeBytes = 5;

constexpr uint8_t kReportIDGet = 0x01;
constexpr uint8_t kReportIDSet = 0x00;

constexpr uint8_t kCmdRelayOn = 0xff;
constexpr uint8_t kCmdRelayOff = 0xfd;
constexpr uint8_t kCmdSetModuleName = 0xfa;

} // namespace dcttech
} // namespace hidapi
} // namespace tests
} // namespace usbrelaymodule
} // namespace nkhlab