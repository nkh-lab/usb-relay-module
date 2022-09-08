#include <bitset>
#include <iomanip>
#include <iostream>

#include "hidapi.h"

#include "DcttechConstants.h"
#include "utils.h"

using namespace nlab::tests::hidapi::dcttech;
using namespace nlab::utils;

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
                data[0] = kReportIDSet;
                data[1] = relay_val;
                data[2] = relay_idx;

                std::cout << "hid_send_feature_report(" << PrintBytes(data, sizeof(data)) << ") ";
                // int ret = hid_write(handle, data, sizeof(data)); // On Ubuntu it works as well
                int ret = hid_send_feature_report(handle, data, sizeof(data));
                std::cout << "returned " << ret << "\n";
                if (ret != -1)
                {
                    std::cout << PrintBytes(data, sizeof(data)) << "\n";
                }
                else
                    main_ret = EXIT_FAILURE;
            }
            else
                printf("hid_open_path(%s) returned -1\n", dev->path);

            hid_close(handle);
        }
    }

    return main_ret;
}

/* Example of output:

$ ./SetRelayStateTest 1 1
hid_send_feature_report(00 ff 01 00 00 00 00 00 00) returned 9
00 ff 01 00 00 00 00 00 00

*/