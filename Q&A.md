### How to install cm compiler? There are only support/scripts/build.bash

Call support/scripts/build.bash -i install_folder

If still have some error message when use BUILD_OPTION after installed cmc and igc 
```clang: error: unable to execute command: Executable "/usr/lib/llvm-6.0/bin/GenX_IR" doesn't exist!```

Please check the cmc in the install folder. if it is a link " /usr/bin/cmc -> clang-6.0".  remove it and directly copy cmc from build.64.linux/, cmc will fix it ASAP
       
### How to get IGA(iga64)?

Please make sure you have build and installed igc. then make sure you are using "Bash" not "Dash", delete line 3 "set -o igncr" in scripts/generate_makefiles.sh then call build_all.sh. 

### How to set default driver name to iHD?

Two option: 
1. export LIBVA_DRIVER_NAME=iHD
2. call vaSetDriverName API

### How to use iHD driver with Gstreamer-vaapi plugin?
export GST_VAAPI_ALL_DRIVERS=1