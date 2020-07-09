# High Level Cross Component Sharing SW Arch

In Linux, details about allocation information like tiling and compression are not kept centrally in KMD. KMD only knows about addresses that are used. Today for example, if the Mesa driver knew the target of an allocation will be an Intel display, it will allocate a surface as X tile, else it allocates it as linear to be compatible for sharing.

The high level design for sharing compression cross components is for the app (i.e. compositor) to negotiate the modifiers across the different drivers. 

1. Drivers report modifiers supported based on allocation information.


2. Then upon surface creation, the driver can get a list of modifiers to use from the app, but it creates only with 1.

3. Upon import or export, only a single modifier is sent.

   

* **DRM Internal Repo**: [https://tf-amr-1.devtools.intel.com/ctf/code/projects.otc_gen_graphics/git/scm.drm_intel/tree ](https://tf-amr-1.devtools.intel.com/ctf/code/projects.otc_gen_graphics/git/scm.drm_intel/tree)
* **DRM Open Source Repo**: [https://github.com/freedesktop/drm-tip ](https://github.com/freedesktop/drm-tip)



## Modifiers

* [https://gitlab.freedesktop.org/mesa/mesa/-/blob/master/include/drm-uapi/drm_fourcc.h](https://gitlab.freedesktop.org/mesa/mesa/-/blob/master/include/drm-uapi/drm_fourcc.h)

* [https://github.com/intel/media-driver/blob/master/media_driver/linux/common/os/i915/include/uapi/drm_fourcc.h](https://github.com/intel/media-driver/blob/master/media_driver/linux/common/os/i915/include/uapi/drm_fourcc.h)

```c++
#define I915_FORMAT_MOD_X_TILED	fourcc_mod_code(INTEL, 1) 
#define I915_FORMAT_MOD_Y_TILED	fourcc_mod_code(INTEL, 2)
#define I915_FORMAT_MOD_Yf_TILED fourcc_mod_code(INTEL, 3)
#define I915_FORMAT_MOD_Y_TILED_CCS	fourcc_mod_code(INTEL, 4)
#define I915_FORMAT_MOD_Yf_TILED_CCS	fourcc_mod_code(INTEL, 5)
#define I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS fourcc_mod_code(INTEL, 6)
#define I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS fourcc_mod_code(INTEL, 7)
```

It is expected that on platforms with different implementation of compression or tiling, a new modifier is defined.



## New Memory Type

* [https://github.com/intel/libva/blob/master/va/va_drmcommon.h](https://github.com/intel/libva/blob/master/va/va_drmcommon.h)

* [https://github.com/intel/libva/blob/master/va/va.h](https://github.com/intel/libva/blob/master/va/va.h)

Below are the memory types supported for surface sharing/creation:

```
VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2             0x40000000 
```

The new memory type *VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2* indicates to use the struct *VAPrimeSurfaceDescriptor*. 

In va_drmcommon.h, you will see that when the memory type is *DRM PRIME*, *VADRMPRIMESurfaceDescriptor* structure is used. In this case the modifier could be passed through the unused planes in this data structure. 

* [https://github.com/intel/libva/blob/master/va/va_drmcommon.h](https://github.com/intel/libva/blob/master/va/va_drmcommon.h)

```c++
typedef struct _VADRMPRIMESurfaceDescriptor {
	    /** Pixel format fourcc of the whole surface (VA_FOURCC_*). */
	    uint32_t fourcc;
	    /** Width of the surface in pixels. */
	    uint32_t width;
	    /** Height of the surface in pixels. */
	    uint32_t height;
	    /** Number of distinct DRM objects making up the surface. */
	    uint32_t num_objects;
	    /** Description of each object. */
	    struct {
	        /** DRM PRIME file descriptor for this object. */
	        int fd;
	        /** Total size of this object (may include regions which are
	         *  not part of the surface). */
	        uint32_t size;
	        /** Format modifier applied to this object. */
	        uint64_t drm_format_modifier;
	    } objects[4];

```

The reason for migrating to *DRM_PRIME_2* memory type is to have better support for inter-operating (sharing buffers) with OGL/OCL and other drivers. The other memory types can share buffers with other drivers but it doesn’t support all of the new buffer types (e.g. compressed), thus the reason to migrate to the new *DRM_PRIME_2* memory type. To get tiling information, previously drivers need to call IOCTL to KMD to get the tiling information. These memory types are not inter-changeable and shouldn’t be changed after creation, but all memory types can be exported to *DRM_PRIME_2* type. 


## Media Driver Default Behavior

We document the default behavior of the media driver with respect to compression and various memory types.

The driver will enable compression for allocations that it can, via *vaCreateImage()* or *vaCreateSurfaces2()*. 

By default, if not specified the memory type, the driver creates the surface internally, and driver will determine the compression and tiling layout.              

If a surface is created with vaCreateSurface2() and indicates memory type as DRM_PRIME_2, it means the surface is allocated externally, and the caller indicates the compression and tiling layout via modifiers.

- ### Plane Offset

Because each driver allocates the CCS planes, these offsets also need to be passed along with the modifiers in the *VADRMPRIMESurfaceDescriptor* structure.

VAAPI uses order Y, UV, Y CCS, UV CCS:

```c++
    /** Number of layers making up the surface. */
	    uint32_t num_layers;
	    /** Description of each layer in the surface. */
	    struct {
	        /** DRM format fourcc of this layer (DRM_FOURCC_*). */
	        uint32_t drm_format;
	        /** Number of planes in this layer. */
	        uint32_t num_planes;
	        /** Index in the objects array of the object containing each
	         *  plane. */
	        uint32_t object_index[4];
	        /** Offset within the object of each plane. */
	        uint32_t offset[4];
	        /** Pitch of each plane. */
	        uint32_t pitch[4];
	    } layers[4];
	} VADRMPRIMESurfaceDescriptor;

```



- ### VA API Surface Allocations

This section will first describe how the VA API driver must report support for compression flavors. 

There are 3 ways VA API access and share allocations; “import”, “create” and “export” mechanisms. Each will be described.



- ### Query of Supported Memory type

*vaQuerySurfaceAttributes()* to return VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 support.

In response to *vaQuerySurfaceAttributes()*, driver returns:

```c++
VASurfaceAttribMemoryType = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2
VASurfaceAttribExternalBufferDescriptor = VADRMPRIMESurfaceDescriptor
```



- ### Import Mechanism

Import is used when an external allocation is shared to VA API driver.

*vaCreateSurfaces2()* with 

```c++
VASurfaceAttribExternalBufferDescriptor = VADRMPRIMESurfaceDescriptor
```


- ### Create Mechanism

Create is used when the VA API driver allocates the resource.

*vaCreateSurface2()* without *VASurfaceAttribExternalBufferDescriptor*



- ### Export Mechanism

Export is used when a resource that the VA API driver has allocated is shared with another driver component.

*vaExportSurfaceHandle()* with mem_type *VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2* and *VAPrimeSurfaceDescriptor* returned. 

By default if no mem_type is specified the media driver will allocate with *VA_SURFACE_ATTRIB_MEM_TYPE_VA* to indicate it is a native Libva allocation. This and all of the memory types can be exported to a *DRM_PRIME_2 mem_type* using *vaExportSurfaceHandle().*

```c++
VAStatus vaExportSurfaceHandle(VADisplay dpy,
	                               VASurfaceID surface_id,
	                               uint32_t mem_type, uint32_t flags,
	                               void *descriptor);
```