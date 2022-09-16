## Module name inaccessible on Linux
**Issue:**
```
./getrelay 
path:             /dev/hidraw4
vendor_id:        0x16c0
product_id:       0x05df
serial_number:    
release_number:   256
manufacturer:     www.dcttech.com
product:          USBRelay2
interface_number: 0
module_name:      < ERROR: Inaccessible! >
```

**Fix:**

Check file permissions of your device:
```
ls -l /dev/hidraw4
crw------- 1 root root 508, 4 sep 15 15:18 /dev/hidraw4
```

For **quick fix** solution `sudo` can be used:
```
sudo ./getrelay 
```

Or configure **udev rules**:

1. Create udev rules file, e.g.:
```
sudo touch /etc/udev/rules.d/91-usbrelay.rules 
```
2. Add rule:
```
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="05df", MODE="0666", GROUP="plugdev"
```
3. Check if your user in `plugdev` group:
```
groups
adm dialout cdrom sudo dip plugdev docker
```
4. If no, add:
```
sudo usermod -aG plugdev $LOGNAME
```
5. Apply new rules:
```
sudo udevadm control --reload-rules
```
6. Unplug/plug USB relay module.

In the [examples](examples) folder you can find an example of udev rules file [91-usbrelay.rules](examples/linux/udev/91-usbrelay.rules).


