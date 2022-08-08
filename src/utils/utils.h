#pragma once

#include <string>

#include "hidapi.h"

#define NOT_USED(x) static_cast<void>(x)

namespace nrelay {
namespace utils {

std::string BytesToStr(uint8_t* bytes, size_t size);
std::string PwstrToStr(wchar_t* pwstr);
std::string HidDeviceInfoToStr(hid_device_info* dev);

} // namespace utils
} // namespace nrelay