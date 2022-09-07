#pragma once

#include <string>

#include "hidapi.h"

namespace nlab {

std::string HidDeviceInfoToStr(hid_device_info* dev);

} // namespace nlab