# Installation Steps
## Add package repository
Agama provides package repository support, it's required to add the source list on your environment following below introduction.
### Red Hat
```
sudo dnf install -y 'dnf-command(config-manager)'
sudo dnf config-manager \
  --add-repo \
  https://repositories.intel.com/graphics/rhel/$VERSION$/intel-graphics.repo
```
***Note: the $VERSION$ in command line is Red Hat version, like 8.4, 8.3, etc.*** 
### SUSE
```
sudo zypper addrepo -r \
  https://repositories.intel.com/graphics/sles/$VERSION$/intel-graphics.repo
```
***Note: the $VERSION$ in command line is SUSE version, like 15sp1, 15sp2, etc.*** 
### Ubuntu
```
sudo apt-get install -y gpg-agent wget
wget -qO - https://repositories.intel.com/graphics/intel-graphics.key |
  sudo apt-key add -
sudo apt-add-repository \
  'deb [arch=amd64] https://repositories.intel.com/graphics/ubuntu $CODE_NAME main'
```
***Note: the $CODE_NAME in command line is Ubuntu code name, like bionic, focal, etc.***
## Install run-time packages
Media stack packages name are slightly different between SLES/RHEL rpm package and Ubuntu deb packages. The libdrm-dev is also necessary for media stack, but original OSV image always contains suitable libdrm-dev version, so no need to install it specifically. The media-driver  package depends on Libva and GmmLib which would be installed automatically once you install media-driver, so no need to explicitly install GmmLib and Libva.
<table border="1">  
  <tr>
    <th width=auto></th> 
    <th width=300>SLES</th>  
    <th width=300>RHEL</th>  
    <th width=300>Ubuntu</th>  
  </tr>  
  <tr>  
    <td>Install steps</td>  
    <td>
  $ sudo zypper --no-gpg-checks install -y \<br>
  intel-media-driver \<br>
  libigfxcmrt7 \<br>
  libmfxgen1 \<br>
  libvpl2 \<br>
  libvpl-tools \<br>
  libmfx1 \<br>
  libva-utils
    </td>  
    <td>
  $ sudo dnf --nogpgcheck install -y \<br>
  intel-media-driver \<br>
  intel-mediasdk \<br>
  libvpl2 \<br>
  libvpl-tools \<br>
  libmfxgen1 \<br>
  libva-utils
    </td>  
    <td>
 $ sudo apt install -y \<br>
  intel-media-va-driver-non-free \<br>
  libmfx1 \<br>
  libigfxcmrt7 \<br>
  libmfxgen1 \<br>
  libvpl2 \<br>
  libvpl-tools \<br>
  vainfo
    </td>
  </tr>
  <tr>  
    <td>Agama Media packages</td>  
    <td>
  libva2 <br>
  libva-devel <br> 
  libva-glx2  <br>
  libva-x11-2  <br>
  libva-drm2  <br>
  libva-wayland2  <br>
  libva-utils  <br>
  intel-media-driver  <br>
  libmfx-utils  <br>
  libmfx-devel  <br>
  libmfx1  <br>
  libmfxgen1  <br>
  libigdgmm11  <br>
  libigdgmm-devel  <br>
  libigfxcmrt7  <br>
  libigfxcmrt-devel  <br>
  libvpl-devel  <br>
  libvpl-tools  <br>
  libvpl2
    </td>  
    <td>
  libva  <br>
  libva-devel  <br>
  libva-utils  <br>
  intel-gmmlib  
  intel-gmmlib-devel  <br>
  intel-media-driver  <br>
  intel-media-driver-devel  <br>
  intel-mediasdk  <br>
  intel-mediasdk-devel  <br>
  intel-mediasdk-utils  <br>
  libmfxgen1  <br>
  libvpl-devel  <br>
  libvpl-tools  <br>
  libvpl2
    </td>  
    <td>
  libva2  <br>
  libva-dev  <br>
  libva-drm2  <br>
  libva-glx2  <br>
  libva-wayland2 <br> 
  libva-x11-2  <br>
  va-driver-all  <br>
  vainfo  <br>
  intel-media-va-driver-non-free  <br>
  libigdgmm11  <br>
  libigdgmm11-dev  <br>
  libigfxcmrt7  <br>
  libigfxcmrt-dev  <br>
  libmfx1  <br>
  libmfx-dev  <br>
  libmfx-tools  <br>
  libmfxgen1  <br>
  libvpl-dev  <br>
  libvpl-tools  <br>
  libvpl2
    </td>
  </tr>
</table>

## Validate Media
After media packages installed, there is a helpful application vainfo could provide basic media status. In SLES/RHEL packages, vainfo is combined in libva-utils rpm package. Here is an example on TGL Ubuntu system
```
$ vainfo
libva info: VA-API version 1.7.0
libva info: Trying to open /usr/lib/x86_64-linux-gnu/dri/iHD_drv_video.so
libva info: Found init function __vaDriverInit_1_7
libva info: va_openDriver() returns 0
vainfo: VA-API version: 1.7 (libva 2.6.0)
vainfo: Driver version: Intel iHD driver for Intel(R) Gen Graphics - 20.1.1 ()
vainfo: Supported profile and entrypoints
      VAProfileNone                   : VAEntrypointVideoProc
      VAProfileNone                   : VAEntrypointStats
      VAProfileMPEG2Simple            : VAEntrypointVLD
      VAProfileMPEG2Simple            : VAEntrypointEncSlice
      VAProfileMPEG2Main              : VAEntrypointVLD
      VAProfileMPEG2Main              : VAEntrypointEncSlice
      VAProfileH264Main               : VAEntrypointVLD
      VAProfileH264Main               : VAEntrypointEncSlice
      VAProfileH264Main               : VAEntrypointFEI
      VAProfileH264Main               : VAEntrypointEncSliceLP
      VAProfileH264High               : VAEntrypointVLD
      VAProfileH264High               : VAEntrypointEncSlice
      VAProfileH264High               : VAEntrypointFEI
      VAProfileH264High               : VAEntrypointEncSliceLP
      VAProfileVC1Simple              : VAEntrypointVLD
      VAProfileVC1Main                : VAEntrypointVLD
      VAProfileVC1Advanced            : VAEntrypointVLD
      VAProfileJPEGBaseline           : VAEntrypointVLD
      VAProfileJPEGBaseline           : VAEntrypointEncPicture
      VAProfileH264ConstrainedBaseline: VAEntrypointVLD
      VAProfileH264ConstrainedBaseline: VAEntrypointEncSlice
      VAProfileH264ConstrainedBaseline: VAEntrypointFEI
      VAProfileH264ConstrainedBaseline: VAEntrypointEncSliceLP
      VAProfileHEVCMain               : VAEntrypointVLD
      VAProfileHEVCMain               : VAEntrypointEncSlice
      VAProfileHEVCMain               : VAEntrypointFEI
      VAProfileHEVCMain               : VAEntrypointEncSliceLP
      VAProfileHEVCMain10             : VAEntrypointVLD
      VAProfileHEVCMain10             : VAEntrypointEncSlice
      VAProfileHEVCMain10             : VAEntrypointEncSliceLP
      VAProfileVP9Profile0            : VAEntrypointVLD
      VAProfileVP9Profile1            : VAEntrypointVLD
      VAProfileVP9Profile2            : VAEntrypointVLD
      VAProfileVP9Profile3            : VAEntrypointVLD
      VAProfileHEVCMain12             : VAEntrypointVLD
      VAProfileHEVCMain12             : VAEntrypointEncSlice
      VAProfileHEVCMain422_10         : VAEntrypointVLD
      VAProfileHEVCMain422_10         : VAEntrypointEncSlice
      VAProfileHEVCMain422_12         : VAEntrypointVLD
      VAProfileHEVCMain422_12         : VAEntrypointEncSlice
      VAProfileHEVCMain444            : VAEntrypointVLD
      VAProfileHEVCMain444            : VAEntrypointEncSliceLP
      VAProfileHEVCMain444_10         : VAEntrypointVLD
      VAProfileHEVCMain444_10         : VAEntrypointEncSliceLP
      VAProfileHEVCMain444_12         : VAEntrypointVLD
      VAProfileHEVCSccMain            : VAEntrypointVLD
      VAProfileHEVCSccMain10          : VAEntrypointVLD
      VAProfileHEVCSccMain444         : VAEntrypointVLD
```
If you want to run an sanity check for media whole stack including GPU RT together, there are couple sample tools available for example as below.
```
$ sample_decode h265 -i input.265 -o output.yuv -hw
```