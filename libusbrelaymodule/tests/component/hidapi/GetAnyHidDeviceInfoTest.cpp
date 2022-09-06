#include <iostream>

#include "hidapi.h"

#include "hidapicpp/utils.h"
#include "utils.h"

using namespace nlab::utils;
using namespace nlab::hidapicpp::utils;

int main(int argc, char const* argv[])
{
    NOT_USED(argc);

    hid_device_info* dev = hid_enumerate(0, 0);

    if (dev)
        std::cout << HidDeviceInfoToStr(dev);
    else
        printf("No USB HID device!\n");

    return 0;
}

/* Example of output:

path:             /dev/hidraw1
vendor_id:        0x413c
product_id:       0x2113
serial_number:
release_number:   264
manufacturer:     (null)
product:          Dell KB216 Wired Keyboard
interface_number: 0

*/