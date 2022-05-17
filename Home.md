
## Media Stack Introduction
![image](https://user-images.githubusercontent.com/34122804/167241733-4904858c-93c5-4e6b-bf2b-8a1b26f1e967.png)

Media stack includes MediaSDK, oneVPL GPU part, public API Libva, Libva-utils, user mode drivers media-driver and GmmLib for memory management. **This repo is for user mode media driver.**<br/>
Application is able to access media stack by oneVPL/MediaSDK dispatcher or Libva directly. Libva-utils provides some examples and basic media status checker. oneVPL is the primary path after ADL platforms.

Below table shows the repos of these components.
| Component           | Repo                                                            |
| ------------------- | --------------------------------------------------------------- |
| media driver        | https://github.com/intel/media-driver                           |
| libva               | https://github.com/intel/libva                                  |
| libva-utils         | https://github.com/intel/libva-utils                            |
| Gmmlib              | https://github.com/intel/gmmlib                                 |
| oneVPL-GPU-RT       | https://github.com/oneapi-src/oneVPL-intel-gpu                  |
| oneVPL Dispatcher   | https://github.com/oneapi-src/oneVPL                            |
| oneVPL sample       | https://github.com/oneapi-src/oneVPL/tree/master/tools/legacy   |
| MediaSDK RT         | https://github.com/Intel-Media-SDK/MediaSDK                     |
| MediaSDK dispatcher | https://github.com/Intel-Media-SDK/MediaSDK                     |
| MediaSDK sample     | https://github.com/Intel-Media-SDK/MediaSDK/tree/master/samples |
| KMD:i915 kernel     | Stable: https://www.kernel.org/ <br/>Latest: https://github.com/freedesktop/drm-tip                                 |