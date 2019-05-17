## Environment Preparation
Ubuntu 16.04+ as example:
```
$ sudo apt-get install autoconf libtool libdrm-dev xorg xorg-dev openbox libx11-dev libgl1-mesa-glx libgl1-mesa-dev libelf-dev
```

## Build drm kernel
Choose the source code or binary to download then build/install it in your local environment.

### Build kernel for legacy platform
These steps are created for media-driver Gen8/9 CI/bi-weekly/quarterly cycles.

1. Download stable kernel from https://www.kernel.org/
2. Build kernel by below cmd.
```
$ make defconfig
$ make -j8
$ sudo make modules_install
$ sudo make install
```

### Build ICL VE
VE patch will be helpful for performance improvement, which will enable and use second VDBox in HW dec/enc. Any cases which can benefit from 2 VDBox will have performance improvement, ex. multiple decode, multiple VDEnc encode, transcode(decode+encode). Take AVC VDEnc CQP TU7 transocde with 1080p as example, VE will bring around 50% performance improvement.
```
$ git clone ssh://people.freedesktop.org/~tursulin/drm-intel
$ git checkout -b my_drm media
$ make defconfig
$ make -j8
$ sudo make modules_install
$ sudo make install
```

### Build ICL SSEU
SSEU patch is needed for full open source build in AVC VDEnc TU1 mode, which call open source kernel HME. HME kernel uses VME HW for motion estimation. There are half subslices without VME HW on ICL. So we need to use the SSEU KMD patch to shut down the non-VME subslices when we run VME encode. Otherwise, it will hang the GPU.
```
$ git clone https://anongit.freedesktop.org/git/drm-intel.git
$ git checkout -b my_drm drm-intel-fixes-2019-03-20
$ make defconfig
$ make -j8
$ sudo make modules_install
$ sudo make install
```

## Build Libva
Libva will be installed to /usr/lib/x86_64-linux-gnu by below commands.
```
$ git clone https://github.com/intel/libva.git
$ ./autogen.sh --prefix=/usr --libdir=/usr/lib/x86_64-linux-gnu
$ make -j8
$ make install
```

## Build Gmmlib
```
$ git clone https://github.com/intel/gmmlib.git
$ cd gmmlib && mkdir build && cd build
$ cmake ..
$ make -j8
$ make install
```

## Build Media Driver
Download driver source code and create workspace like
```
<workspace>
    |- media-driver
    |- build_media
```

Build driver by below commands.
```
$ git clone https://github.com/intel/media-driver
$ mkdir build_media
$ cd build_media
```

Media driver support different build options. Full feature build is default build option including all features enabled. Open source build(pre-build open source kernel) feature support detail in [open source build features](https://github.com/intel/media-driver#features-in-open-source-build).

### 1. Full feature build(default)
```
$ cmake ../media-driver
```

### 2. Open source build(pre-build open source kernel)
```
$ cmake ../media-driver -DENABLE_NONFREE_KERNELS=OFF
```

Then build and install it by below commands.
```
$ make -j8
$ sudo make install
```

In Ubuntu, driver will be installed in /usr/lib/x86_64-linux-gnu/dri, so need to export below environment.
```
$ export LIBVA_DRIVERS_PATH=/usr/lib/x86_64-linux-gnu/dri
$ export LIBVA_DRIVER_NAME=iHD
```

### Build VE UMD patch
If you want to enable VE(Virtual Engine), you could use below PR to include UMD change.
```
$ git fetch origin pull/283/head
$ git checkout -b ve FETCH_HEAD
```

## Build FFmpeg
Download ffmpeg package from http://ffmpeg.org/download.html, current version is https://ffmpeg.org/releases/ffmpeg-4.1.tar.bz2
```
$ sudo apt-get install build-essential
$ tar -jxvf ffmpeg-4.1.tar.bz2
$ cd ffmpeg-4.1
$ ./configure --disable-x86asm
$ make -j8
$ make install
```

## Run FFmpeg test
Download clips from http://fate-suite.ffmpeg.org/h264-conformance/, like CABA1_SVA_B.264, create content/avc folder to storage them. Add "-hwaccel vaapi -hwaccel_device /dev/dri/renderD128" in ffmpeg cmd to make sure use HW acceleration.

### VE enabling
FFmpeg AVC VDEnc TU7 transcode command example for VE patch.
```
$./ffmpeg -y -hwaccel vaapi -vaapi_device /dev/dri/renderD128 -hwaccel_output_format vaapi -i content/avc/CABA1_SVA_B.264 -frames 2000 -c:v h264_vaapi -compression_level 7 -profile:v high -level:v 40 -g 31 -qp 28 -bf 2 -low_power 1 avc_vdenc_TU7_CQP_xcode.mp4
```

### SSEU enabling
FFmpeg AVC VDEnc TU1 transcode command example for SSEU patch.
```
$./ffmpeg -y -hwaccel vaapi -vaapi_device /dev/dri/renderD128 -hwaccel_output_format vaapi -i content/avc/CABA1_SVA_B.264 -frames 2000 -c:v h264_vaapi -compression_level 1 -profile:v high -level:v 40 -g 31 -qp 28 -bf 2 -low_power 1 avc_vdenc_TU1_xcode.mp4
```