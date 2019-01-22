list these QA, some of them will be fixed in near future.

Q. how to install cm compiler. there are only support/scripts/build.bash

A. call support/scripts/build.bash -i install_folder

Q. still have some error message when use BUILD_OPTION after installed cmc and igc 
         clang: error: unable to execute command: Executable "/usr/lib/llvm-6.0/bin/GenX_IR" doesn't exist!

A. please check the cmc in the install folder. if it is a link " /usr/bin/cmc -> clang-6.0".  remove it and directly copy cmc from build.64.linux/, cmc will fix it ASAP
       
Q. how to get iga (iga64) 

A. please make sure you have build and installed igc. then make sure you are using "Bash" not "Dash", delete line 3 "set -o igncr" in scripts/generate_makefiles.sh. call build_all.sh. 

Q. How to set default driver name to iHD

A. two option: 1. export LIBVA_DRIVER_NAME=iHD   2. call vaSetDriverName API

Q. How to use iHD driver with Gstreamer-vaapi plugin
A. export GST_VAAPI_ALL_DRIVERS=1