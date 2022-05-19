# Environment Preparation
Here will take Ubuntu as the example.
For Ubuntu 16.04+
```bash
apt install autoconf libtool libdrm-dev xorg xorg-dev openbox libx11-dev libgl1-mesa-glx libgl1-mesa-dev
```
Equivalents for other distributions should work.

# Building & Install
1. Build and install [LibVA](https://github.com/intel/libva)
2. Build and install [GmmLib](https://github.com/intel/gmmlib) following [GmmLib compatibility](https://github.com/intel/media-driver/wiki/Compatibility-with-GmmLib)
3. Get media repo and format the workspace folder as below (suggest the workspace to be a dedicated one for media driver build):
```
<workspace>
    |- media-driver
```
4. Create build_media new folder under your workspace
```bash
$ mkdir <workspace>/build_media
```
Then the workspace looks like below
```
<workspace>
    |- media-driver
    |- build_media
```
Then
```bash
$ cd <workspace>/build_media
$ cmake ../media-driver
$ make -j"$(nproc)"
$ sudo make install
```
This will install the following files (e.g. on Ubuntu):
```
-- Installing: /usr/lib/x86_64-linux-gnu/dri/iHD_drv_video.so
-- Installing: /etc/profile.d/intel-media.sh
-- Installing: /usr/lib/x86_64-linux-gnu/igfxcmrt64.so
```
For iHD_drv_video.so please export related LIBVA environment variables.
```
export LIBVA_DRIVERS_PATH=<path-contains-iHD_drv_video.so>
export LIBVA_DRIVER_NAME=iHD
```

