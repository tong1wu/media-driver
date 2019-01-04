## Overview

Video processing is an essential component in media driver, we have some tools for debugging purpose, including surface dump, driver log, ddi log etc. 

## Driver version

Install media release-internal or debug driver. Please note, release-internal or debug are needed; release version can not support this debug tool for performance and efficiency.

## Registry key

$vim /etc/igfx_user_feature.txt (Add below Key path if it's not exist.)

[KEY]

0x00000001

UFKEY_INTERNAL\LibVa

### To dump VP input/output surface

$mkdir /data/vp_dump (Surfaces will be dumped in this file folder, please make sure this file folder is writable.)

Add below keys to /etc/igfx_user_feature.txt under "UFKEY_INTERNAL\LibVa". 

1) "preAll" means the input surface of video processing, "postAll" means the output surface of video processing. 
2) If the input surface "preAll" is correct, but the output surface "postAll" is corrupted, probably the issue is in video processing driver. 
3) If the input surface "preAll" is corrupted, please check the component of the pipeline before video processing.
4) If the output surface "postAll" is correct, please check the component of the pipeline after video processing.

[VALUE]

outfileLocation

1

/data/vp_dump/

[VALUE]

dumpLocations

1

preAll,postAll

### To dump VP HLT log

Add below keys to /etc/igfx_user_feature.txt under "UFKEY_INTERNAL\LibVa". It will print some logs on the screen which will give you some hints about driver behavior.

[VALUE]

Message Print Enabled

4

1

[VALUE]

Message HLT Enabled

4

1

[VALUE]

VP Message Tags

4

7

[VALUE]

DDI Message Tags

4

7

### To dump VP DDI Trace log

This tool dump the parameters in video processing driver device interface(DDI). It will help you to check if the parameters is expected(which app or media framework passed to driver).

$mkdir /data

$export  VPDDI_TRACE=/data/vpddi.log
