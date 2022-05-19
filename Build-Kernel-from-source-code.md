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
$ sudo make modules_install
$ sudo make install
```
# Install the kernel
```bash
$ sudo make modules_install install
```
Or if you don't have sudo installed, run
```bash
$ su -c "make modules_install install"
```