# Environment Preparation
Here will take Ubuntu as the example.

Ubuntu 18.04+ requires additional packages:
```bash 
$ sudo apt-get install libncurses5-dev flex bison gcc make git exuberant-ctags bc libssl-dev
```
# Build kernel
Download stable kernel from https://www.kernel.org/
```bash 
$ git clone https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
```
Or the latest kernel from https://github.com/freedesktop/drm-tip
```bash 
$ git clone https://github.com/freedesktop/drm-tip.git
```
Then build kernel by below commands.
```bash
$ cp /boot/config-`uname -r`* .config
$ make defconfig
$ make -j8
```
# Install the kernel
```bash
$ sudo make modules_install install
```
Or if you don't have sudo installed, run
```bash
$ su -c "make modules_install install"
```
# GuC/HuC firmware
In some cases, we need GuC/HuC supporting, otherwise some features will be missed.
You use below commands to check the status of GuC/HuC.

## Check GuC status
```bash
$ cat /sys/kernel/debug/dri/0/gt/uc/guc_info
GuC firmware: i915/tgl_guc_49.0.1.bin
        status: MISSING
        version: wanted 49.0, found 0.0
        uCode: 0 bytes
        RSA: 0 bytes

GuC status 0x00000001:
        Bootrom status = 0x0
        uKernel status = 0x0
        MIA Core status = 0x0

Scratch registers:
         0:     0x0
         1:     0x0
         2:     0x0
         3:     0x0
         4:     0x0
         5:     0x0
         6:     0x0
         7:     0x0
         8:     0x0
         9:     0x0
        10:     0x0
        11:     0x0
        12:     0x0
        13:     0x0
        14:     0x0
        15:     0x0
```
If you get status=MISSING, you need to:
1. Download corresponding firmware at https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/tree/i915
2. Copy the firmware binary to /lib/firmware/i915
3. Run below command with *root*
```
# update-initramfs -u
# reboot
```
4. After the machine rebooted, you will get
```
# cat /sys/kernel/debug/dri/0/gt/uc/guc_info
GuC firmware: i915/tgl_guc_49.0.1.bin
        status: RUNNING
        version: wanted 49.0, found 49.0
        uCode: 321408 bytes
        RSA: 256 bytes

GuC status 0x8002f077:
        Bootrom status = 0x3b
        uKernel status = 0xf0
        MIA Core status = 0x2

Scratch registers:
         0:     0x0
         1:     0x1dbfd3
         2:     0x0
         3:     0x4000
         4:     0x40
         5:     0x3dc
         6:     0x0
         7:     0x0
         8:     0x0
         9:     0x0
        10:     0x0
        11:     0x0
        12:     0x0
        13:     0x0
        14:     0x0
        15:     0x0
```
## Check HuC status
```
# cat /sys/kernel/debug/dri/0/gt/uc/huc_info
HuC firmware: i915/tgl_huc_7.5.0.bin
        status: RUNNING
        version: wanted 7.5, found 7.5
        uCode: 580352 bytes
        RSA: 256 bytes
HuC status: 0x00090001
```
If you don't get normal result, please use the same processing method to update HuC firmware binary.
### Note: On some platforms, you need to add additional parameters in kernel boot command.(i915.enable_guc=2 i915.force_probe=*)