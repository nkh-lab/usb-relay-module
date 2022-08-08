#pragma once

namespace nrelay {
namespace constants {

constexpr uint16_t kUsbVendorId = 0x16c0;
constexpr uint16_t kUsbProductId = 0x05df;

constexpr size_t kDataSizeBytes = 9;

constexpr uint8_t kReportIDGetFeature = 0x01;
constexpr uint8_t kReportIDReadWrite = 0x00;

constexpr uint8_t kCmdRelayOn = 0xff;
constexpr uint8_t kCmdRelayOff = 0xfd;
constexpr uint8_t kCmdSetModuleName = 0xfa;

} // namespace constants
} // namespace nrelay