#include "HidapiUtils.h"

#include "Utils.h"

#include <iomanip>
#include <sstream>

using namespace nlab::utils;

namespace nlab {

std::string HidDeviceInfoToStr(hid_device_info* dev)
{
    std::stringstream ss;

    ss << "path:             " << dev->path << "\n";
    ss << std::hex;
    ss << "vendor_id:        0x" << std::setfill('0') << std::setw(4) << dev->vendor_id << "\n";
    ss << "product_id:       0x" << std::setfill('0') << std::setw(4) << dev->product_id << "\n";
    ss << std::dec; // back to dec
    ss << "serial_number:    " << PwstrToStr(dev->serial_number) << "\n";
    ss << "release_number:   " << dev->release_number << "\n";
    ss << "manufacturer:     " << PwstrToStr(dev->manufacturer_string) << "\n";
    ss << "product:          " << PwstrToStr(dev->product_string) << "\n";
    ss << "interface_number: " << dev->interface_number << "\n";

    return ss.str();
}

} // namespace nlab