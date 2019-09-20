| Configuration| OS | CMAKE/configuration options | Compiler | Environment|
|---|---|---|---|---|
| build-release | CentOS 7.3 | -DINSTALL_DRIVER_SYSCONF=OFF -DBUILD_TYPE=release | gcc-6.3.1 | x11, wayland, opencl |
| build-debug | CentOS 7.3 | -DINSTALL_DRIVER_SYSCONF=OFF -DBUILD_TYPE=debug | gcc-6.3.1 | x11, wayland, opencl |
| build-release-internal | CentOS 7.3 | -DINSTALL_DRIVER_SYSCONF=OFF -DBUILD_TYPE=release-internal | gcc-6.3.1 | x11, wayland, opencl |
| build-gcc-9.2.0 | CentOS 7.3 | -DINSTALL_DRIVER_SYSCONF=OFF -DBUILD_TYPE=release | gcc-9.2.0 | x11, wayland, opencl |

See [conf_media_driver.py](https://github.com/Intel-Media-SDK/product-configs/blob/master/conf_media_driver.py) for detailed CI configurations and command lines and  also [Media SDK CI build](https://github.com/Intel-Media-SDK/MediaSDK/wiki/Media-SDK-CI-build-configurations) configurations.