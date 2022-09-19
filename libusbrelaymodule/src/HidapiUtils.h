#pragma once

#include <string>

#include "hidapi.h"

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

std::string HidDeviceInfoToStr(hid_device_info* dev);

}
} // namespace usbrelaymodule
} // namespace nkhlab