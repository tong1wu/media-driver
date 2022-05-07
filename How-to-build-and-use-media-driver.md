# Build media driver on Ubuntu
## Prerequisites
For Ubuntu 16.04 and above. (Equivalents for other distributions should work)

$ sudo apt-get install autoconf libtool libdrm-dev xorg xorg-dev openbox libx11-dev libgl1-mesa-glx libgl1-mesa-dev xutils-dev
## Dependencies
Before building media driver, we need to build libva first. (we need to rebuild if libva(VAAPI) update or changes)

Get libva:

$ git clone https://github.com/intel/libva.git

Build and install

$ cd libva 

$ ./autogen.sh --prefix=/usr --libdir=/usr/lib/x86_64-linux-gnu

$ make -j8

$ sudo make install

## Build media driver

$ git clone https://github.com/intel/gmmlib.git

$ cd gmmlib/

$ mkdir build && cd build

$ cmake -DCMAKE_INSTALL_PREFIX=/usr/ -DCMAKE_BUILD_TYPE=ReleaseInternal ..
  (this command is building release internal version)

$ make -j8

$ sudo make install

$ git clone https://github.com/intel/media-driver.git

$ mkdir build_media

$ cd build_media

$ cmake -DCMAKE_INSTALL_PREFIX=/usr ../media-driver

(If building debug or release internal version, please use this command:
$ cmake -DCMAKE_INSTALL_PREFIX=/usr  -DBUILD_TYPE=release-internal ../media-driver)

$ make -j8

## Use the built media driver

After the building, we can use the generated iHD_drv_video.so(/build_media/media-driver) to replace the one at /usr/lib/x86_64-linux-gnu/dri/iHD_drv_video.so.

## Check the current media driver

We can use vainfo to check if the current media driver is working or not. 

$ export LIBVA_DRIVERS_PATH=/usr/lib/x86_64-linux-gnu/dri/

$ export LIBVA_DRIVER_NAME=iHD

$ vainfo

If you are seeing this on the screen, that shows media driver is working. Have a fun!

libva info: VA-API version 1.4.0

libva info: va_getDriverName() returns 0

libva info: User requested driver 'iHD'

libva info: Trying to open /usr/lib/x86_64-linux-gnu/dri//iHD_drv_video.so

libva info: Found init function __vaDriverInit_1_4

libva info: va_openDriver() returns 0

vainfo: VA-API version: 1.4 (libva 2.0.1.pre1)

vainfo: Driver version: Intel iHD driver - 1.0.0

vainfo: Supported profile and entrypoints

[LIBVA]:ENTER    - DdiMedia_QueryConfigProfiles

[LIBVA]:ENTER    - DdiMedia_QueryConfigEntrypoints

