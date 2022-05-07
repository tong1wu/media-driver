
## Media Stack Introduction
![image](https://user-images.githubusercontent.com/48201750/167239923-d38ab33f-58ae-470a-8594-b1e147886b74.png)

Media stack includes MediaSDK, oneVPL GPU part, public API Libva, Libva-utils, user mode drivers media-driver and GmmLib for memory management.<br/>
Application is able to access media stack by oneVPL/MediaSDK dispatcher or Libva directly. Libva-utils provides some examples and basic media status checker. oneVPL is the primary path after ADL platforms. MediaSDK RT doesn't support ADL+ platforms, so MediaSDK dispatcher would go to oneVPL-GPU-RT path.<br\>
**This repo is for user mode media driver.** 