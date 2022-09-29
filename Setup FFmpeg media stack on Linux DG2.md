ACM and ATS-M kernel is under upstreaming so the building steps are slightly different with upstream kernel. Please follow up below introduction for ACM and ATS-M environment setup.

## Environment Preparation

Ubuntu 18.04+ requires additional packages:
```bash
$ sudo apt-get install dkms debhelper devscripts build-essential gawk libncurses5-dev flex bison gcc make git exuberant-ctags bc libssl-dev
```

## Build and install kernel

Current media-driver was verified against[intel_gpu_i915_backports](https://github.com/intel-gpu/intel-gpu-i915-backports). Follow below steps to setup kernel and gpu-firmware

* Clone the repo and checkout to ubuntu/main branch

```bash
$ git clone https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
$ git checkout ubuntu/main
```
* Follow the [README](https://github.com/intel-gpu/intel-gpu-i915-backports/tree/ubuntu/main) to download the DKMS and correlated Kernel version
* Download and load firmware follwoing [Build-Kernel-From-Source-Code](https://github.com/intel/media-driver/wiki/Build-Kernel-from-source-code), but the firmware should be downloaded from [intel-gpu-firmware](https://github.com/intel-gpu/intel-gpu-firmware)
* Follow the README from [intel-gpu-firmware](https://github.com/intel-gpu/intel-gpu-firmware) to download and load the firmware.
* On DG2 you need to add additional parameters (enable_guc=2) in kernel boot command.
```bash
$ sudo vim /etc/default/grub
GRUB_CMDLINE_LINUX_DEFAULT="net.ifnames=0 biosdevname=0 console=ttyS0,115200n8 console=tty1 ignore_loglevel i915.enable_guc=2"

$ sudo updata-grub
$ sudo reboot
```
* Follow [Build-Kernel-From-Source-Code](https://github.com/intel/media-driver/wiki/Build-Kernel-from-source-code) to check the GuC/HuC status.

## Build and install media-driver, libva, gmmlib, Onevpl, FFmpeg in one script

* Set environment variable by creating env.sh. NOTE: You can change the USER and git config variables by yourself.
 ```bash
$ touch env.sh
#!/bin/bash
USER="gta"
W_HOME="/home/${USER}"

export ROOT_INSTALL_DIR=/home/${USER}/media-env/media/build
mkdir -p $ROOT_INSTALL_DIR
export SRC_DIR=/home/${USER}/media-env/media/src
mkdir -p $SRC_DIR
export PKG_CONFIG_PATH=$ROOT_INSTALL_DIR/lib/pkgconfig/:$ROOT_INSTALL_DIR/lib/x86_64-linux-gnu/pkgconfig:$PKG_CONFIG_PATH
export LD_LIBRARY_PATH=$ROOT_INSTALL_DIR/lib:$ROOT_INSTALL_DIR/lib/mfx/:$ROOT_INSTALL_DIR/lib/xorg/:$ROOT_INSTALL_DIR/lib/x86_64-linux-gnu:/usr/local/lib:$LD_LIBRARY_PATH
export PATH=$ROOT_INSTALL_DIR/bin:$PATH
export LIBVA_DRIVER_NAME=iHD
export LIBVA_DRIVERS_PATH=$ROOT_INSTALL_DIR/lib/dri

$ source env.sh
```
* Build and install the component in on script
   ```bash
   $ cd ~
   $ touch build_install.sh
   #!/bin/bash
    USER="gta"
    W_HOME="/home/${USER}"
    SOFTWARE_DIR="${W_HOME}/media-env"
    MEDIA_DIR="${SOFTWARE_DIR}/media"
    MEDIA_SRC_DIR="${MEDIA_DIR}/src"

    build_dir()
    {
        if [ ! -d "$SOFTWARE_DIR" ]; then
            mkdir -p "$SOFTWARE_DIR"
        fi

        if [ ! -d "$MEDIA_DIR" ]; then
            mkdir -p "$MEDIA_DIR"
        fi

        if [ ! -d "$MEDIA_SRC_DIR" ]; then
            mkdir -p "$MEDIA_SRC_DIR"
        fi
    }
    build_media_prerequest()
    {
        sudo apt-get install -y cifs-utils autoconf libtool libdrm-dev yasm libghc-x11-dev libxmuu-dev libxfixes-dev libxcb-glx0-dev libgegl-dev libegl1-mesa-dev
        sudo apt-get install -y git xutils-dev libpciaccess-dev xserver-xorg-dev cmake xutils-dev
        sudo apt-get install -y libv4l-dev python2
        sudo apt-get install -y libasound2-dev
        sudo apt-get install -y libsdl2-dev meson ninja-build libx265-dev libx264-dev libde265*
        sudo apt-get install gudev*

    }
    build_libva()
    {
        echo "*********************************************libva*********************************************"
        cd ${MEDIA_SRC_DIR}
        if [ ! -d "${MEDIA_SRC_DIR}/libva" ]; then
            git clone https://github.com/intel/libva.git libva
        fi
        cd ${MEDIA_SRC_DIR}/libva
        git clean -dfx
        git pull
        ./autogen.sh --prefix=$ROOT_INSTALL_DIR
        make -j16 && make install
    }
    build_libva_utils()
    {
        echo "*********************************************libva-utils****************************************"
        cd ${MEDIA_SRC_DIR}
        if [ ! -d "${MEDIA_SRC_DIR}/libva-utils" ]; then
            git clone https://github.com/intel/libva-utils.git libva-utils
        fi
        cd ${MEDIA_SRC_DIR}/libva-utils
        git clean -dfx
        git pull
        ./autogen.sh --prefix=$ROOT_INSTALL_DIR --enable-tests
        make -j16 && make install
    }
    build_gmmlib()
    {
        echo "***************************************gmmlib**********************************"
        cd ${MEDIA_SRC_DIR}
        if [ ! -d "${MEDIA_SRC_DIR}/gmmlib" ]; then
            git clone https://github.com/intel/gmmlib gmmlib
        fi
        cd ${MEDIA_SRC_DIR}/gmmlib
        git clean -dfx
        git pull
        mkdir -p build && cd build
        cmake $MEDIA_SRC_DIR/gmmlib -DCMAKE_INSTALL_PREFIX=$ROOT_INSTALL_DIR
        make -j16 && make install
    }
    build_media_driver()
    {
        echo "*********************************************media-driver*******************************************"
        cd ${MEDIA_SRC_DIR}
        if [ ! -d "${MEDIA_SRC_DIR}/media-driver" ]; then
            git clone https://github.com/intel/media-driver media-driver
        fi
        cd ${MEDIA_SRC_DIR}/media-driver
        git clean -dfx
        git pull
        mkdir -p build && cd build
        cmake $MEDIA_SRC_DIR/media-driver -DCMAKE_INSTALL_PREFIX=$ROOT_INSTALL_DIR -DENABLE_PRODUCTION_KMD=ON
        make -j16 && make install
    }
    build_vpl_dispatcher()
    {
        echo "*****************************************vpl_dispatcher******************************************************"
        cd ${MEDIA_SRC_DIR}
        if [ ! -d "${MEDIA_SRC_DIR}/vpl_dispatcher" ]; then
            git clone https://github.com/oneapi-src/oneVPL.git vpl_dispatcher
        fi
        cd ${MEDIA_SRC_DIR}/vpl_dispatcher
        git clean -dfx
        git pull
        mkdir -p build && cd build
        cmake  $MEDIA_SRC_DIR/vpl_dispatcher -DCMAKE_INSTALL_PREFIX=$ROOT_INSTALL_DIR
        cmake --build . --config Release --target install
    }
    build_vpl_runtime()
    {
        echo "*****************************************vpl_runtime******************************************************"
        cd ${MEDIA_SRC_DIR}
        if [ ! -d "${MEDIA_SRC_DIR}/vpl_runtime" ]; then
            git clone -b main https://github.com/oneapi-src/oneVPL-intel-gpu.git vpl_runtime
        fi
        cd ${MEDIA_SRC_DIR}/vpl_runtime
        git clean -dfx
        git pull

        mkdir -p build && cd build
        cmake $MEDIA_SRC_DIR/vpl_runtime -DCMAKE_INSTALL_PREFIX=$ROOT_INSTALL_DIR
        make -j8 && make install
    }
    build_ffmpeg()
    {
        echo "*********************************************ffmpeg-qsv*************************************************"
        cd ${MEDIA_SRC_DIR}
        if [ ! -d "${MEDIA_SRC_DIR}/cartwheel-ffmpeg" ]; then
            git clone https://github.com/intel-media-ci/cartwheel-ffmpeg --recursive cartwheel-ffmpeg
        fi
        git pull
        git submodule update --init --recursive
        cd ${MEDIA_SRC_DIR}/cartwheel-ffmpeg/ffmpeg
        git clean -dfx
        git config --global user.name "username"
        git config --global user.email "user@email"
        git am ../patches/*.patch
        ./configure --prefix=$ROOT_INSTALL_DIR --enable-shared --enable-vaapi --enable-libvpl --enable-gpl --enable-libx264 --enable-libx265
        make -j16 && make install
    }



    build_dir
    build_media_prerequest
    build_libva
    build_libva_utils
    build_gmmlib
    build_media_driver
    build_vpl_dispatcher
    build_vpl_runtime
    build_ffmpeg

    $ sh build_install.sh
   ```

