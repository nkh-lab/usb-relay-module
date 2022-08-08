#include <bitset>
#include <iomanip>
#include <iostream>

#include "hidapi.h"

#include "constants.h"
#include "utils.h"

using namespace nrelay::constants;
using namespace nrelay::utils;

int main(int argc, char const* argv[])
{
    int main_ret = EXIT_SUCCESS;

    if (argc < 3)
    {
        std::cout << "Please provide argumnets: <relay-index> <value 0 or 1>\n";
        main_ret = EXIT_FAILURE;
    }
    else
    {
        hid_device_info* dev = hid_enumerate(kUsbVendorId, kUsbProductId);
        if (dev)
        {
            hid_device* handle = hid_open_path(dev->path);
            if (handle)
            {
                uint8_t relay_idx = std::stoi(argv[1]);
                uint8_t relay_val = std::stoi(argv[2]) == 1 ? kCmdRelayOn : kCmdRelayOff;

                uint8_t data[kDataSizeBytes] = {0};
                data[0] = kReportIDReadWrite;
                data[1] = relay_val;
                data[2] = relay_idx;

                //int ret = hid_write(handle, data, sizeof(data)); // On Ubuntu it works as well
                int ret = hid_send_feature_report(handle, data, sizeof(data));
                if (ret != -1) main_ret = EXIT_FAILURE;

                //printf("hid_write() returned %d\n", ret);
                printf("hid_send_feature_report() returned %d\n", ret);
                std::cout << std::hex;
                for (int i = 0; i < sizeof(data); ++i)
                    std::cout << std::setfill('0') << std::setw(2) << static_cast<int>(data[i]) << " ";
                std::cout << std::dec; // back to dec
                std::cout << "\n";
            }
            else
                printf("hid_open_path(%s) returned -1\n", dev->path);

            hid_close(handle);
        }
    }

    return main_ret;
}

/* Example of output:

$ ./SetRelayStateTest 2 1
hid_write() returned 9
00 ff 02 00 00 00 00 00 00

*/