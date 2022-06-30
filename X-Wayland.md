libva support X11, Wayland, DRM. it could get vendor information though these protocols, but if it is a Xwayland usage, an issue will happen:
libva assume app is run under X11 window system, so it will call dri2 extension to query the vendor information to get the backend driver name, but unfortunately, xwayland has no dri2 support. the call will failed, so it will report "va_getDriverName() failed" or "va_getDriverNameByIndex() failed"

there are no perfect solution now (libva should add dri3 support, because dri3 api could be used under xwayland usage), the quick WA is:

export LIBVA_DRIVER_NAME=XXX (if you are using media_driver, XXX is iHD)