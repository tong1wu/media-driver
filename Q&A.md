Q. how to install cm compiler. there are only support/scripts/build.bash
A. call support/scripts/build.bash -i install_folder

Q. still have some error message when use BUILD_OPTION after installed cmc and igc 
         clang: error: unable to execute command: Executable "/usr/lib/llvm-6.0/bin/GenX_IR" doesn't exist!
A. please check the cmc in the install folder. if it is a link " /usr/bin/cmc -> clang-6.0".  remove it and directly copy cmc from build.64.linux/, cmc will fix it ASAP
       
Q. how to build iga (iga64)
A. please make sure you are using "Bash" not "Dash", then delete line 3 "set -o igncr" in scripts/generate_makefiles.sh. call build_all.sh. 
