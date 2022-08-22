#pragma once

#include <string>

#include "hidapi.h"

namespace urm {
namespace hidapicpp {
namespace utils {

std::string HidDeviceInfoToStr(hid_device_info* dev);

}
} // namespace hidapicpp
} // namespace urm