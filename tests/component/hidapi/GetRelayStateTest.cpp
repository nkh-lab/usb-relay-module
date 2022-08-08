#include <bitset>
#include <iostream>

#include "hidapi.h"

#include "constants.h"
#include "utils.h"

using namespace nrelay::constants;
using namespace nrelay::utils;

int main(int argc, char const* argv[])
{
    NOT_USED(argc);

    hid_device_info* dev = hid_enumerate(kUsbVendorId, kUsbProductId);
    if (dev)
    {
        std::cout << HidDeviceInfoToStr(dev);

        hid_device* handle = hid_open_path(dev->path);
        if (handle)
        {
            uint8_t data[kDataSizeBytes] = {0};
            data[0] = kReportIDGetFeature;

            std::cout << "==============================\n";
            std::cout << "hid_get_feature_report(" << BytesToStr(data, sizeof(data)) << ") ";
            int ret = hid_get_feature_report(handle, data, sizeof(data));
            std::cout << "returned " << ret << "\n";
            if (ret != -1)
            {
                std::cout << BytesToStr(data, sizeof(data)) << "\n";

                std::string board_name(reinterpret_cast<char*>(data), 5);
                std::cout << "board_name:       " << board_name << "\n";
                std::cout << "relays_state:     " << std::bitset<8>(data[7]) << "\n";
            }
        }
        else
            printf("hid_open_path(%s) returned -1\n", dev->path);

        hid_close(handle);
    }

    return 0;
}

/* Example of output:

$ ./GetRelayStateTest
path:             /dev/hidraw4
vendor_id:        0x16c0
product_id:       0x05df
serial_number:
release_number:   256
manufacturer:     www.dcttech.com
product:          USBRelay2
interface_number: 0
==============================
hid_get_feature_report(01 00 00 00 00 00 00 00 00) returned 9
52 31 00 00 00 00 00 01 52
board_name:       R1
relays_state:     00000001

*/
