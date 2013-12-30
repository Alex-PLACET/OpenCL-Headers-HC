/*******************************************************************************
 * Copyright (c) 2008-2013 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and/or associated documentation files (the
 * "Materials"), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 ******************************************************************************/

/* $Revision: 11928 $ on $Date: 2010-07-13 09:04:56 -0700 (Tue, 13 Jul 2010) $ */

/* cl_ext.h contains OpenCL extensions which don't have external */
/* (OpenGL, D3D) dependencies.                                   */

#ifndef __CL_EXT_H
#define __CL_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __APPLE__
        #include <OpenCL/cl.h>
    #include <AvailabilityMacros.h>
#else
        #include <CL/cl.h>
#endif

/* cl_khr_fp64 extension - no extension #define since it has no functions  */
#define CL_DEVICE_DOUBLE_FP_CONFIG                  0x1032

/* cl_khr_fp16 extension - no extension #define since it has no functions  */
#define CL_DEVICE_HALF_FP_CONFIG                    0x1033

/* Memory object destruction
 *
 * Apple extension for use to manage externally allocated buffers used with cl_mem objects with CL_MEM_USE_HOST_PTR
 *
 * Registers a user callback function that will be called when the memory object is deleted and its resources 
 * freed. Each call to clSetMemObjectCallbackFn registers the specified user callback function on a callback 
 * stack associated with memobj. The registered user callback functions are called in the reverse order in 
 * which they were registered. The user callback functions are called and then the memory object is deleted 
 * and its resources freed. This provides a mechanism for the application (and libraries) using memobj to be 
 * notified when the memory referenced by host_ptr, specified when the memory object is created and used as 
 * the storage bits for the memory object, can be reused or freed.
 *
 * The application may not call CL api's with the cl_mem object passed to the pfn_notify.
 *
 * Please check for the "cl_APPLE_SetMemObjectDestructor" extension using clGetDeviceInfo(CL_DEVICE_EXTENSIONS)
 * before using.
 */
#define cl_APPLE_SetMemObjectDestructor 1
cl_int  CL_API_ENTRY clSetMemObjectDestructorAPPLE(  cl_mem /* memobj */, 
                                        void (* /*pfn_notify*/)( cl_mem /* memobj */, void* /*user_data*/), 
                                        void * /*user_data */ )             CL_EXT_SUFFIX__VERSION_1_0;  


/* Context Logging Functions
 *
 * The next three convenience functions are intended to be used as the pfn_notify parameter to clCreateContext().
 * Please check for the "cl_APPLE_ContextLoggingFunctions" extension using clGetDeviceInfo(CL_DEVICE_EXTENSIONS)
 * before using.
 *
 * clLogMessagesToSystemLog fowards on all log messages to the Apple System Logger 
 */
#define cl_APPLE_ContextLoggingFunctions 1
extern void CL_API_ENTRY clLogMessagesToSystemLogAPPLE(  const char * /* errstr */, 
                                            const void * /* private_info */, 
                                            size_t       /* cb */, 
                                            void *       /* user_data */ )  CL_EXT_SUFFIX__VERSION_1_0;

/* clLogMessagesToStdout sends all log messages to the file descriptor stdout */
extern void CL_API_ENTRY clLogMessagesToStdoutAPPLE(   const char * /* errstr */, 
                                          const void * /* private_info */, 
                                          size_t       /* cb */, 
                                          void *       /* user_data */ )    CL_EXT_SUFFIX__VERSION_1_0;

/* clLogMessagesToStderr sends all log messages to the file descriptor stderr */
extern void CL_API_ENTRY clLogMessagesToStderrAPPLE(   const char * /* errstr */, 
                                          const void * /* private_info */, 
                                          size_t       /* cb */, 
                                          void *       /* user_data */ )    CL_EXT_SUFFIX__VERSION_1_0;


/************************ 
* cl_khr_icd extension *                                                  
************************/
#define cl_khr_icd 1

/* cl_platform_info                                                        */
#define CL_PLATFORM_ICD_SUFFIX_KHR                  0x0920

/* Additional Error Codes                                                  */
#define CL_PLATFORM_NOT_FOUND_KHR                   -1001

extern CL_API_ENTRY cl_int CL_API_CALL
clIcdGetPlatformIDsKHR(cl_uint          /* num_entries */,
                       cl_platform_id * /* platforms */,
                       cl_uint *        /* num_platforms */);

typedef CL_API_ENTRY cl_int (CL_API_CALL *clIcdGetPlatformIDsKHR_fn)(
    cl_uint          /* num_entries */,
    cl_platform_id * /* platforms */,
    cl_uint *        /* num_platforms */);


/* Extension: cl_khr_image2D_buffer
 *
 * This extension allows a 2D image to be created from a cl_mem buffer without a copy.
 * The type associated with a 2D image created from a buffer in an OpenCL program is image2d_t.
 * Both the sampler and sampler-less read_image built-in functions are supported for 2D images
 * and 2D images created from a buffer.  Similarly, the write_image built-ins are also supported
 * for 2D images created from a buffer.
 *
 * When the 2D image from buffer is created, the client must specify the width,
 * height, image format (i.e. channel order and channel data type) and optionally the row pitch
 *
 * The pitch specified must be a multiple of CL_DEVICE_IMAGE_PITCH_ALIGNMENT pixels.
 * The base address of the buffer must be aligned to CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT pixels.
 */
    
/*************************************
 * cl_khr_initalize_memory extension *
 *************************************/
    
#define CL_CONTEXT_MEMORY_INITIALIZE_KHR            0x200E
    
    
/**************************************
 * cl_khr_terminate_context extension *
 **************************************/
    
#define CL_DEVICE_TERMINATE_CAPABILITY_KHR          0x200F
#define CL_CONTEXT_TERMINATE_KHR                    0x2010

#define cl_khr_terminate_context 1
extern CL_API_ENTRY cl_int CL_API_CALL clTerminateContextKHR(cl_context /* context */) CL_EXT_SUFFIX__VERSION_1_2;

typedef CL_API_ENTRY cl_int (CL_API_CALL *clTerminateContextKHR_fn)(cl_context /* context */) CL_EXT_SUFFIX__VERSION_1_2;
    
    
/*
 * Extension: cl_khr_spir
 *
 * This extension adds support to create an OpenCL program object from a 
 * Standard Portable Intermediate Representation (SPIR) instance
 */

#define CL_DEVICE_SPIR_VERSIONS                     0x40E0
#define CL_PROGRAM_BINARY_TYPE_INTERMEDIATE         0x40E1


/******************************************
* cl_nv_device_attribute_query extension *
******************************************/
/* cl_nv_device_attribute_query extension - no extension #define since it has no functions */
#define CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV       0x4000
#define CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV       0x4001
#define CL_DEVICE_REGISTERS_PER_BLOCK_NV            0x4002
#define CL_DEVICE_WARP_SIZE_NV                      0x4003
#define CL_DEVICE_GPU_OVERLAP_NV                    0x4004
#define CL_DEVICE_KERNEL_EXEC_TIMEOUT_NV            0x4005
#define CL_DEVICE_INTEGRATED_MEMORY_NV              0x4006
#define CL_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT_NV   0x4007
#define CL_DEVICE_PCI_BUS_ID_NV                     0x4008
#define CL_DEVICE_PCI_SLOT_ID_NV                    0x4009

/*********************************
* cl_amd_device_memory_flags *
*********************************/
#define cl_amd_device_memory_flags 1

#define CL_MEM_USE_PERSISTENT_MEM_AMD       (1 << 6)        // Alloc from GPU's CPU visible heap

/* cl_device_info */
#define CL_DEVICE_MAX_ATOMIC_COUNTERS_EXT           0x4032

/*********************************
* cl_amd_device_attribute_query *
*********************************/
#define CL_DEVICE_PROFILING_TIMER_OFFSET_AMD        0x4036
#define CL_DEVICE_TOPOLOGY_AMD                      0x4037
#define CL_DEVICE_BOARD_NAME_AMD                    0x4038
#define CL_DEVICE_GLOBAL_FREE_MEMORY_AMD            0x4039
#define CL_DEVICE_SIMD_PER_COMPUTE_UNIT_AMD         0x4040
#define CL_DEVICE_SIMD_WIDTH_AMD                    0x4041
#define CL_DEVICE_SIMD_INSTRUCTION_WIDTH_AMD        0x4042
#define CL_DEVICE_WAVEFRONT_WIDTH_AMD               0x4043
#define CL_DEVICE_GLOBAL_MEM_CHANNELS_AMD           0x4044
#define CL_DEVICE_GLOBAL_MEM_CHANNEL_BANKS_AMD      0x4045
#define CL_DEVICE_GLOBAL_MEM_CHANNEL_BANK_WIDTH_AMD 0x4046
#define CL_DEVICE_LOCAL_MEM_SIZE_PER_COMPUTE_UNIT_AMD   0x4047
#define CL_DEVICE_LOCAL_MEM_BANKS_AMD               0x4048
#define CL_DEVICE_THREAD_TRACE_SUPPORTED_AMD        0x4049

typedef union
{
    struct { cl_uint type; cl_uint data[5]; } raw;
    struct { cl_uint type; cl_char unused[17]; cl_char bus; cl_char device; cl_char function; } pcie;
} cl_device_topology_amd;
#define CL_DEVICE_TOPOLOGY_TYPE_PCIE_AMD            1

/**************************
* cl_amd_offline_devices *
**************************/
#define CL_CONTEXT_OFFLINE_DEVICES_AMD              0x403F

#ifdef CL_VERSION_1_1
   /***********************************
    * cl_ext_device_fission extension *
    ***********************************/
    #define cl_ext_device_fission   1
    
    extern CL_API_ENTRY cl_int CL_API_CALL
    clReleaseDeviceEXT( cl_device_id /*device*/ ) CL_EXT_SUFFIX__VERSION_1_1; 
    
    typedef CL_API_ENTRY cl_int 
    (CL_API_CALL *clReleaseDeviceEXT_fn)( cl_device_id /*device*/ ) CL_EXT_SUFFIX__VERSION_1_1;

    extern CL_API_ENTRY cl_int CL_API_CALL
    clRetainDeviceEXT( cl_device_id /*device*/ ) CL_EXT_SUFFIX__VERSION_1_1; 
    
    typedef CL_API_ENTRY cl_int 
    (CL_API_CALL *clRetainDeviceEXT_fn)( cl_device_id /*device*/ ) CL_EXT_SUFFIX__VERSION_1_1;

    typedef cl_ulong  cl_device_partition_property_ext;
    extern CL_API_ENTRY cl_int CL_API_CALL
    clCreateSubDevicesEXT(  cl_device_id /*in_device*/,
                            const cl_device_partition_property_ext * /* properties */,
                            cl_uint /*num_entries*/,
                            cl_device_id * /*out_devices*/,
                            cl_uint * /*num_devices*/ ) CL_EXT_SUFFIX__VERSION_1_1;

    typedef CL_API_ENTRY cl_int 
    ( CL_API_CALL * clCreateSubDevicesEXT_fn)(  cl_device_id /*in_device*/,
                                                const cl_device_partition_property_ext * /* properties */,
                                                cl_uint /*num_entries*/,
                                                cl_device_id * /*out_devices*/,
                                                cl_uint * /*num_devices*/ ) CL_EXT_SUFFIX__VERSION_1_1;

    /* cl_device_partition_property_ext */
    #define CL_DEVICE_PARTITION_EQUALLY_EXT             0x4050
    #define CL_DEVICE_PARTITION_BY_COUNTS_EXT           0x4051
    #define CL_DEVICE_PARTITION_BY_NAMES_EXT            0x4052
    #define CL_DEVICE_PARTITION_BY_NAMES_INTEL          0x4052
    #define CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN_EXT  0x4053
    
    /* clDeviceGetInfo selectors */
    #define CL_DEVICE_PARENT_DEVICE_EXT                 0x4054
    #define CL_DEVICE_PARTITION_TYPES_EXT               0x4055
    #define CL_DEVICE_AFFINITY_DOMAINS_EXT              0x4056
    #define CL_DEVICE_REFERENCE_COUNT_EXT               0x4057
    #define CL_DEVICE_PARTITION_STYLE_EXT               0x4058
    
    /* clGetImageInfo enum */
    #define CL_IMAGE_BYTE_PITCH_AMD                     0x4059

    /* error codes */
    #define CL_DEVICE_PARTITION_FAILED_EXT              -1057
    #define CL_INVALID_PARTITION_COUNT_EXT              -1058
    #define CL_INVALID_PARTITION_NAME_EXT               -1059
    
    /* CL_AFFINITY_DOMAINs */
    #define CL_AFFINITY_DOMAIN_L1_CACHE_EXT             0x1
    #define CL_AFFINITY_DOMAIN_L2_CACHE_EXT             0x2
    #define CL_AFFINITY_DOMAIN_L3_CACHE_EXT             0x3
    #define CL_AFFINITY_DOMAIN_L4_CACHE_EXT             0x4
    #define CL_AFFINITY_DOMAIN_NUMA_EXT                 0x10
    #define CL_AFFINITY_DOMAIN_NEXT_FISSIONABLE_EXT     0x100
    
    /* cl_device_partition_property_ext list terminators */
    #define CL_PROPERTIES_LIST_END_EXT                  ((cl_device_partition_property_ext) 0)
    #define CL_PARTITION_BY_COUNTS_LIST_END_EXT         ((cl_device_partition_property_ext) 0)
    #define CL_PARTITION_BY_NAMES_LIST_END_EXT          ((cl_device_partition_property_ext) 0 - 1)
    #define CL_PARTITION_BY_NAMES_LIST_END_INTEL        ((cl_device_partition_property_ext) 0 - 1)
	
	#define CL_QUEUE_THREAD_LOCAL_EXEC_ENABLE_INTEL      (1 << 31)

	/* cl_ext_atomic_counters_32 and cl_ext_atomic_counters_64 extensions 
     * no extension #define since they have no functions                                              
     */
    #define CL_DEVICE_MAX_ATOMIC_COUNTERS_EXT           0x4032
	
/*********************************
* cl_qcom_ext_host_ptr extension
*********************************/

#define CL_MEM_EXT_HOST_PTR_QCOM                  (1 << 29)

#define CL_DEVICE_EXT_MEM_PADDING_IN_BYTES_QCOM   0x40A0      
#define CL_DEVICE_PAGE_SIZE_QCOM                  0x40A1
#define CL_IMAGE_ROW_ALIGNMENT_QCOM               0x40A2
#define CL_IMAGE_SLICE_ALIGNMENT_QCOM             0x40A3
#define CL_MEM_HOST_UNCACHED_QCOM                 0x40A4
#define CL_MEM_HOST_WRITEBACK_QCOM                0x40A5
#define CL_MEM_HOST_WRITETHROUGH_QCOM             0x40A6
#define CL_MEM_HOST_WRITE_COMBINING_QCOM          0x40A7

typedef cl_uint                                   cl_image_pitch_info_qcom;

extern CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceImageInfoQCOM(cl_device_id             device,
                         size_t                   image_width,
                         size_t                   image_height,
                         const cl_image_format   *image_format,
                         cl_image_pitch_info_qcom param_name,
                         size_t                   param_value_size,
                         void                    *param_value,
                         size_t                  *param_value_size_ret);

typedef struct _cl_mem_ext_host_ptr
{
    // Type of external memory allocation.
    // Legal values will be defined in layered extensions.
    cl_uint  allocation_type;
            
    // Host cache policy for this external memory allocation.
    cl_uint  host_cache_policy;

} cl_mem_ext_host_ptr;

/*********************************
* cl_qcom_ion_host_ptr extension
*********************************/

#define CL_MEM_ION_HOST_PTR_QCOM                  0x40A8

typedef struct _cl_mem_ion_host_ptr
{
    // Type of external memory allocation.
    // Must be CL_MEM_ION_HOST_PTR_QCOM for ION allocations.
    cl_mem_ext_host_ptr  ext_host_ptr;

    // ION file descriptor
    int                  ion_filedesc;
            
    // Host pointer to the ION allocated memory
    void*                ion_hostptr;

} cl_mem_ion_host_ptr;

#endif /* CL_VERSION_1_1 */

#ifdef CL_VERSION_1_2
    /********************************
    * cl_amd_bus_addressable_memory *
    ********************************/

    /* cl_mem flag - bitfield */
    #define CL_MEM_BUS_ADDRESSABLE_AMD               (1<<30)
    #define CL_MEM_EXTERNAL_PHYSICAL_AMD             (1<<31)

    #define CL_COMMAND_WAIT_SIGNAL_AMD                0x4080
    #define CL_COMMAND_WRITE_SIGNAL_AMD               0x4081
    #define CL_COMMAND_MAKE_BUFFERS_RESIDENT_AMD      0x4082

    typedef struct
    {
        cl_ulong surface_bus_address;
        cl_ulong marker_bus_address;
    } cl_bus_address_amd;

    typedef CL_API_ENTRY cl_int
    (CL_API_CALL * clEnqueueWaitSignalAMD_fn)( cl_command_queue /*command_queue*/,
                                               cl_mem /*mem_object*/,
                                               cl_uint /*value*/,
                                               cl_uint /*num_events*/,
                                               const cl_event * /*event_wait_list*/,
                                               cl_event * /*event*/) CL_EXT_SUFFIX__VERSION_1_2;

    typedef CL_API_ENTRY cl_int
    (CL_API_CALL * clEnqueueWriteSignalAMD_fn)( cl_command_queue /*command_queue*/,
                                                cl_mem /*mem_object*/,
                                                cl_uint /*value*/,
                                                cl_ulong /*offset*/,
                                                cl_uint /*num_events*/,
                                                const cl_event * /*event_list*/,
                                                cl_event * /*event*/) CL_EXT_SUFFIX__VERSION_1_2;

    typedef CL_API_ENTRY cl_int
    (CL_API_CALL * clEnqueueMakeBuffersResidentAMD_fn)( cl_command_queue /*command_queue*/,
                                                 cl_uint /*num_mem_objs*/,
                                                 cl_mem * /*mem_objects*/,
                                                 cl_bool /*blocking_make_resident*/,
                                                 cl_bus_address_amd * /*bus_addresses*/,
                                                 cl_uint /*num_events*/,
                                                 const cl_event * /*event_list*/,
                                                 cl_event * /*event*/) CL_EXT_SUFFIX__VERSION_1_2;

#endif /* CL_VERSION_1_2 */

#if defined DX_MEDIA_SHARING
#include <wtypes.h>
#include <d3d9types.h>
#include <d3d9.h>
typedef cl_uint cl_dx9_device_source_intel;
typedef cl_uint cl_dx9_device_set_intel;
#define CL_D3D9_DEVICE_INTEL                    0x4022
#define CL_DX9_ADAPTER_NAME_INTEL               0x4023
#define CL_D3D9EX_DEVICE_INTEL                  0x4070
#define CL_DXVA_DEVICE_INTEL                    0x4071
#define CL_PREFERRED_DEVICES_FOR_DX9_INTEL      0x4024
#define CL_ALL_DEVICES_FOR_DX9_INTEL            0x4025
#define CL_CONTEXT_D3D9_DEVICE_INTEL            0x4026
#define CL_CONTEXT_D3D9EX_DEVICE_INTEL          0x4072
#define CL_CONTEXT_DXVA_DEVICE_INTEL            0x4073
#define CL_MEM_DX9_RESOURCE_INTEL               0x4027
#define CL_MEM_DX9_SHARED_HANDLE_INTEL          0x4074
#define CL_IMAGE_DX9_PLANE_INTEL                0x4075
#define CL_COMMAND_ACQUIRE_DX9_OBJECTS_INTEL    0x402A
#define CL_COMMAND_RELEASE_DX9_OBJECTS_INTEL    0x402B
#define CL_INVALID_DX9_DEVICE_INTEL             -1010
#define CL_INVALID_DX9_RESOURCE_INTEL           -1011
#define CL_DX9_RESOURCE_ALREADY_ACQUIRED_INTEL  -1012
#define CL_DX9_RESOURCE_NOT_ACQUIRED_INTEL      -1013
#define CL_DX9_OBJECT_SURFACE                0x3002

typedef CL_API_ENTRY cl_mem (CL_API_CALL *clCreateFromDX9MediaSurfaceINTEL_fn)(
    cl_context          /*context*/,
    cl_mem_flags        /*flags*/,
    IDirect3DSurface9 * /*resource*/,
    HANDLE              /*sharedHandle*/,
    UINT                /*plane*/,
    cl_int *            /*errcode_ret*/);
typedef CL_API_ENTRY cl_int (CL_API_CALL *clEnqueueAcquireDX9ObjectsINTEL_fn)(
    cl_command_queue /*command_queue*/,
    cl_uint /*num_objects*/,
    const cl_mem * /*mem_objects*/,
    cl_uint /*num_events_in_wait_list*/,
    const cl_event * /*event_wait_list*/,
    cl_event * /*event*/);
typedef CL_API_ENTRY cl_int (CL_API_CALL *clEnqueueReleaseDX9ObjectsINTEL_fn)(
    cl_command_queue /*command_queue*/,
    cl_uint /*num_objects*/,
    cl_mem * /*mem_objects*/,
    cl_uint /*num_events_in_wait_list*/,
    const cl_event * /*event_wait_list*/,
    cl_event * /*event*/);
typedef CL_API_ENTRY cl_int (CL_API_CALL* clGetDeviceIDsFromDX9INTEL_fn)(
    cl_platform_id /*platform*/,
    cl_dx9_device_source_intel /*dx9_device_source*/,
    void* /*dx9_object*/,
    cl_dx9_device_set_intel /*dx9_device_set*/,
    cl_uint /*num_entries*/, 
    cl_device_id* /*devices*/, 
    cl_uint* /*num_devices*/);
#endif /* DX9_MEDIA_SHARING */

#ifdef __cplusplus
}
#endif


#endif /* __CL_EXT_H */
