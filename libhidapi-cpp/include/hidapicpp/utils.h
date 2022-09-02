#pragma once

#include <string>

#include "hidapi.h"

namespace nlab {
namespace hidapicpp {
namespace utils {

std::string HidDeviceInfoToStr(hid_device_info* dev);

}
} // namespace hidapicpp
} // namespace nlab