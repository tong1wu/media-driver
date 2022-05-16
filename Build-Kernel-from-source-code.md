# Environment Preparation
Here will take Ubuntu as the example.

Ubuntu 18.04+ requires additional packages:
```bash 
$ sudo apt-get install git flex bison libssl-dev
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
$ make defconfig
$ make -j8
$ sudo make modules_install
$ sudo make install
```