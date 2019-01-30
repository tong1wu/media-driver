* [Media codec shaders](#media-codec-shaders)
* [Video processing shaders](#video-processing-shaders)
  - [HDR shaders](#hdr-shaders)
  - [HVSVP shaders](#hvsvp-shaders)
* [CM helper shaders](#cm-helper-shaders)
* [Disable shaders at compile time](#disable-shaders-at-compile-time)
* [Build with closed source shaders](#build-with-closed-source-shaders)

# Media codec shaders

| Binary kernel | Sources |
| ------------- | ------- |
|[media_driver/agnostic/gen8/codec/kernel/igcodeckrn_g8.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen8/codec/kernel/igcodeckrn_g8.c)|Closed source|
|[media_driver/agnostic/gen9/codec/kernel/igcodeckrn_g9.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9/codec/kernel/igcodeckrn_g9.c)|Closed source|
|[media_driver/agnostic/gen9_bxt/codec/kernel/igcodeckrn_g9_bxt.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9_bxt/codec/kernel/igcodeckrn_g9_bxt.c)|Closed source|
|[media_driver/agnostic/gen9_kbl/codec/kernel/igcodeckrn_g9_kbl.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9_kbl/codec/kernel/igcodeckrn_g9_kbl.c)|Closed source|
|[media_driver/agnostic/gen10/codec/kernel/igcodeckrn_g10.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen10/codec/kernel/igcodeckrn_g10.c)|Closed source|
|[media_driver/agnostic/gen11/codec/kernel/igcodeckrn_g11.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen11/codec/kernel/igcodeckrn_g11.c)|Closed source|
|[media_driver/agnostic/gen11_icllp/codec/kernel/igcodeckrn_g11_icllp.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen11_icllp/codec/kernel/igcodeckrn_g11_icllp.c)|Closed source|

The following kernels support a range of features for Gen9 Skylake platform:
* AVC Multi Frame Encoding (MFE)
* AVC FEI encoding
* HEVC FEI encoding

| Binary kernel | Sources |
| ------------- | ------- |
|[media_driver/agnostic/gen9_skl/codec/cmrt_kernel/*.cpp](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9_skl/codec/cmrt_kernel)|Closed source|

# Video processing shaders

| Binary kernel | Sources |
| ------------- | ------- |
|[media_driver/agnostic/gen8/vp/kernel/igvpkrn_g8.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen8/vp/kernel/igvpkrn_g8.c)|Closed source|
|[media_driver/agnostic/gen9/vp/kernel/igvpkrn_g9.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9/vp/kernel/igvpkrn_g9.c)|Closed source|
|[media_driver/agnostic/gen9/vp/kernel/igvpkrn_isa_g9.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9/vp/kernel/igvpkrn_isa_g9.c)|Closed source|
|[media_driver/agnostic/gen10/vp/kernel/igvpkrn_g10.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen10/vp/kernel/igvpkrn_g10.c)|Closed source|
|[media_driver/agnostic/gen11_icllp/vp/kernel/igvpkrn_g11_icllp.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen11_icllp/vp/kernel/igvpkrn_g11_icllp.c)|Closed source|
|[media_driver/agnostic/gen11_icllp/vp/kernel_free/igvpkrn_g11_icllp.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen11_icllp/vp/kernel_free/igvpkrn_g11_icllp.c)|Open [source](https://github.com/intel/media-driver/tree/master/media_driver/agnostic/gen11_icllp/vp/kernel_free/Source)|

## HDR shaders

High Dynamic Range (HDR) Video Processing provides a tone mapping filter for pre-processing and post-processing in transcoding and playback usage scenarios for adjust video for proper rendering on a display.

| Binary kernel | Sources |
| ------------- | ------- |
|[media_driver/agnostic/gen11_icllp/vp/kernel/igvpkrn_isa_g11_icllp.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen11_icllp/vp/kernel/igvpkrn_isa_g11_icllp.c)|Closed source|

## HVSVP shaders

Human Visual System Video Preprocessing (HVSVP) provides an adaptive temporal and spatial filter used for pre-processing in unison with encoding to improve compression efficiency. HVSVP uses encoder QP information plus image analysis to determine appropriate filter strength to achieve best possible compression.

HVSVP has 16 qp-mapping profiles to select how soft or aggressive the user wants the filter to run, where 1 is softests and 16 is most aggressive.

| Binary kernel | Sources |
| ------------- | ------- |
|[media_driver/agnostic/gen9/vp/kernel/igvpkrn_isa_g9.c](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9/vp/kernel/igvpkrn_isa_g9.c)|Closed source|

# CM helper shaders

GPU copy shaders provide a way to accelerate video memory copy operations and avoid some drawbacks associated with copy from system to video memory:

| Binary kernel | Sources |
| ------------- | ------- |
|[media_driver/agnostic/gen8/cm/cm_gpucopy_kernel_g8.h](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen8/cm/cm_gpucopy_kernel_g8.h)|Closed source|
|[media_driver/agnostic/gen9/cm/cm_gpucopy_kernel_g9.h](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9/cm/cm_gpucopy_kernel_g9.h)|Closed source|
|[media_driver/agnostic/gen10/cm/cm_gpucopy_kernel_g10.h](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen10/cm/cm_gpucopy_kernel_g10.h)|Closed source|
|[media_driver/agnostic/gen11/cm/cm_gpucopy_kernel_g11lp.h](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen11/cm/cm_gpucopy_kernel_g11lp.h)|Closed source|

GPU init shaders provide a way to initialize video resource with specific value by using EU for faster initialization operation.

| Binary kernel | Sources |
| ------------- | ------- |
|[media_driver/agnostic/gen8/cm/cm_gpuinit_kernel_g8.h](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen8/cm/cm_gpuinit_kernel_g8.h)|Closed source|
|[media_driver/agnostic/gen9/cm/cm_gpuinit_kernel_g9.h](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen9/cm/cm_gpuinit_kernel_g9.h)|Closed source|
|[media_driver/agnostic/gen10/cm/cm_gpuinit_kernel_g10.h](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen10/cm/cm_gpuinit_kernel_g10.h)|Closed source|
|[media_driver/agnostic/gen11/cm/cm_gpuinit_kernel_g11lp.h](https://github.com/intel/media-driver/blob/master/media_driver/agnostic/gen11/cm/cm_gpuinit_kernel_g11lp.h)|Closed source|

# Disable shaders at compile time

To disable shaders at compile time, configure build with the option -DENABLE_KERNELS=OFF, i.e.:
```sh
cmake -DENABLE_KERNELS=OFF /path/to/media/driver
```
It is possible to physically remove shaders from sources to make sure they don't end up in the build. Please, refer to the following script:
```sh
# Delete (X=8, 9, …):
#   - media_driver/agnostic/gen${X}/codec/kernel
#   - media_driver/agnostic/gen${X}/vp/kernel
#   - media_driver/agnostic/gen${X}/vp/kernel_free
find . -name kernel | grep gen | xargs git rm -r
# Delete (X=8, 9, …):
#   - media_driver/agnostic/gen${X}/codec/kernel_free
#   - media_driver/agnostic/gen${X}/vp/kernel_free
find . -name kernel_free | grep gen | xargs git rm -r

# Delete (X=8, 9, …):
#   - media_driver/agnostic/gen${X}/cm/cm_gpucopy_kernel_g${X}.h
find . -name cm_gpucopy_kernel* | xargs git rm

# Delete:
#   - media_driver/agnostic/gen9_skl/codec/cmrt_kernel
find . -name cmrt_kernel | xargs git rm -r
```
Mind that if folders like `media_driver/agnostic/gen${X}` will be removed, driver will completely lost support for the specified platform.

# Build with open source shaders

To build driver with only open sources shaders, configure build with the option -DENABLE_KERNELS=ON -DENABLE_NONFREE_KERNELS=OFF, i.e.:
```sh
cmake -DENABLE_KERNELS=ON -DENABLE_NONFREE_KERNELS=OFF /path/to/media/driver
```
It is possible to physically remove closed source shaders from sources to make sure they don't end up in the build. Please, refer to the following script:
```sh
# Delete (X=8, 9, …):
#   - media_driver/agnostic/gen${X}/codec/kernel
#   - media_driver/agnostic/gen${X}/vp/kernel
find . -name kernel | grep gen | xargs git rm -r

# Delete (X=8, 9, …):
#   - media_driver/agnostic/gen${X}/cm/cm_gpucopy_kernel_g${X}.h
find . -name cm_gpucopy_kernel* | xargs git rm

# Delete:
#   - media_driver/agnostic/gen9_skl/codec/cmrt_kernel
find . -name cmrt_kernel | xargs git rm -r
```

It is possible to rebuild shaders from sources. For that you need to have Intel Graphics Compiler (IGC) and CM Compiler (CMC) installed:
* https://github.com/intel/cm-compiler
* https://github.com/intel/intel-graphics-compiler

Mind that as of now there are issues around building and installation of these packages on the system:
* https://github.com/intel/intel-graphics-compiler/issues/31
* https://github.com/intel/intel-graphics-compiler/issues/35

Please, make sure that iga64, GenX_IR and cmc are available in the PATH and configure driver as follows:
```sh
cmake -DENABLE_KERNELS=ON -DENABLE_NONFREE_KERNELS=OFF -DBUILD_KERNELS=ON /path/to/media/driver
```

# Build with closed source shaders

To build driver with closed sources shaders, configure build with the option -DENABLE_KERNELS=ON -DENABLE_NONFREE_KERNELS=ON, i.e.:
```sh
cmake -DENABLE_KERNELS=ON -DENABLE_NONFREE_KERNELS=ON /path/to/media/driver
```