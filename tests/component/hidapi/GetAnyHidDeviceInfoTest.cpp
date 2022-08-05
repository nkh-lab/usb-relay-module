#include <iostream>

#include "hidapi.h"

#include "utils.h"

int main(int argc, char const *argv[])
{
    NOT_USED(argc);

    hid_device_info *dev = hid_enumerate(0, 0);

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
        printf("No USB HID device!\n");
    }

    /* code */
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
