#include <iostream>

#include "hidapi.h"

#include "constants.h"
#include "utils.h"

using namespace nrelay::constants;

int main(int argc, char const *argv[])
{
    NOT_USED(argc);

    hid_device_info *dev = hid_enumerate(kUsbVendorId, kUsbProductId);

    if (dev)
    {
        printf("path:             %s\n", dev->path);
		printf("vendor_id:        0x%04hx\n", dev->vendor_id);
		printf("product_id:       0x%04hx\n", dev->product_id);
		printf("serial_number:    %ls\n", dev->serial_number);
		printf("release_number:   %d\n", dev->release_number);
        printf("manufacturer:     %ls\n", dev->manufacturer_string);
        printf("product:          %ls\n", dev->product_string);
		printf("interface_number: %d\n", dev->interface_number);
    }
    else 
    {
        printf("No 0x%04hx 0x%04hx USB Relay device!\n", kUsbVendorId, kUsbProductId);
    }

    /* code */
    return 0;
}