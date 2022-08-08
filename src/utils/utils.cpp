#include "utils.h"

#include <iomanip>
#include <sstream>

namespace nrelay {
namespace utils {

std::string BytesToStr(uint8_t* bytes, size_t size)
{
    std::stringstream ss;

    ss << std::hex;
    for (int i = 0; i < size; ++i)
    {
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(bytes[i]);
        if (i < size - 1) ss << " ";
    }

    return ss.str();
}

std::string PwstrToStr(wchar_t* pwstr)
{
    std::string str = "(null)";
    if (pwstr)
    {
        std::wstring wstr = std::wstring(pwstr);
        str = std::string(wstr.begin(), wstr.end());
    }

    return str;
}

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

} // namespace utils
} // namespace nrelay