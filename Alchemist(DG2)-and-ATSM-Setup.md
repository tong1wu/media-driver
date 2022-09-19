ACM and ATS-M kernel is under upstreaming so the building steps are slightly different with upstream kernel. Please follow up below introduction for ACM and ATS-M environment setup.

## Build and install kernel
Current media-driver was verified against[intel_gpu_i915_backports](https://github.com/intel-gpu/intel-gpu-i915-backports), using below steps to enable the kernel and firmware for ACM.
* Download the DKMS and correlated Kernel version following [README](https://github.com/intel-gpu/intel-gpu-i915-backports#readme)
* Compile and install kernel following[Build-Kernel-From-Source-Code](https://github.com/intel/media-driver/wiki/Build-Kernel-from-source-code)
* Download and load firmware follwoing [Build-Kernel-From-Source-Code](https://github.com/intel/media-driver/wiki/Build-Kernel-from-source-code), but the firmware should be downloaded from [intel-gpu-firmware](https://github.com/intel-gpu/intel-gpu-firmware)

## Build and compile media-driver
Follow the steps in wiki [Build media-driver from source code](https://github.com/intel/media-driver/wiki/Build-media-driver-from-source-code), but it's required to enable build option **ENABLE_PRODUCTION_KMD=ON** when run cmake, like `cmake ../media-driver -DENABLE_PRODUCTION_KMD=ON`.