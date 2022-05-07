
## Media Stack Introduction
![image](https://user-images.githubusercontent.com/48201750/167240299-b293882a-adfe-4804-913f-a7a5918472c6.png)

Media stack includes MediaSDK, oneVPL GPU part, public API Libva, Libva-utils, user mode drivers media-driver and GmmLib for memory management. **This repo is for user mode media driver.**<br/>
Application is able to access media stack by oneVPL/MediaSDK dispatcher or Libva directly. Libva-utils provides some examples and basic media status checker. oneVPL is the primary path after ADL platforms. MediaSDK RT doesn't support ADL+ platforms, so MediaSDK dispatcher would go to oneVPL-GPU-RT path. 