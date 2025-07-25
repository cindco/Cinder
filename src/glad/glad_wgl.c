/*

    WGL loader generated by glad 0.1.36 on Mon Jul  7 08:58:35 2025.

    Language/Generator: C/C++
    Specification: wgl
    APIs: wgl=1.0
    Profile: -
    Extensions:
        WGL_3DFX_multisample,
        WGL_3DL_stereo_control,
        WGL_AMD_gpu_association,
        WGL_ARB_buffer_region,
        WGL_ARB_context_flush_control,
        WGL_ARB_create_context,
        WGL_ARB_create_context_no_error,
        WGL_ARB_create_context_profile,
        WGL_ARB_create_context_robustness,
        WGL_ARB_extensions_string,
        WGL_ARB_framebuffer_sRGB,
        WGL_ARB_make_current_read,
        WGL_ARB_multisample,
        WGL_ARB_pbuffer,
        WGL_ARB_pixel_format,
        WGL_ARB_pixel_format_float,
        WGL_ARB_render_texture,
        WGL_ARB_robustness_application_isolation,
        WGL_ARB_robustness_share_group_isolation,
        WGL_ATI_pixel_format_float,
        WGL_ATI_render_texture_rectangle,
        WGL_EXT_colorspace,
        WGL_EXT_create_context_es2_profile,
        WGL_EXT_create_context_es_profile,
        WGL_EXT_depth_float,
        WGL_EXT_display_color_table,
        WGL_EXT_extensions_string,
        WGL_EXT_framebuffer_sRGB,
        WGL_EXT_make_current_read,
        WGL_EXT_multisample,
        WGL_EXT_pbuffer,
        WGL_EXT_pixel_format,
        WGL_EXT_pixel_format_packed_float,
        WGL_EXT_swap_control,
        WGL_EXT_swap_control_tear,
        WGL_I3D_digital_video_control,
        WGL_I3D_gamma,
        WGL_I3D_genlock,
        WGL_I3D_image_buffer,
        WGL_I3D_swap_frame_lock,
        WGL_I3D_swap_frame_usage,
        WGL_NV_DX_interop,
        WGL_NV_DX_interop2,
        WGL_NV_copy_image,
        WGL_NV_delay_before_swap,
        WGL_NV_float_buffer,
        WGL_NV_gpu_affinity,
        WGL_NV_multigpu_context,
        WGL_NV_multisample_coverage,
        WGL_NV_present_video,
        WGL_NV_render_depth_texture,
        WGL_NV_render_texture_rectangle,
        WGL_NV_swap_group,
        WGL_NV_vertex_array_range,
        WGL_NV_video_capture,
        WGL_NV_video_output,
        WGL_OML_sync_control
    Loader: True
    Local files: False
    Omit khrplatform: False
    Reproducible: False

    Commandline:
        --api="wgl=1.0" --generator="c" --spec="wgl" --extensions="WGL_3DFX_multisample,WGL_3DL_stereo_control,WGL_AMD_gpu_association,WGL_ARB_buffer_region,WGL_ARB_context_flush_control,WGL_ARB_create_context,WGL_ARB_create_context_no_error,WGL_ARB_create_context_profile,WGL_ARB_create_context_robustness,WGL_ARB_extensions_string,WGL_ARB_framebuffer_sRGB,WGL_ARB_make_current_read,WGL_ARB_multisample,WGL_ARB_pbuffer,WGL_ARB_pixel_format,WGL_ARB_pixel_format_float,WGL_ARB_render_texture,WGL_ARB_robustness_application_isolation,WGL_ARB_robustness_share_group_isolation,WGL_ATI_pixel_format_float,WGL_ATI_render_texture_rectangle,WGL_EXT_colorspace,WGL_EXT_create_context_es2_profile,WGL_EXT_create_context_es_profile,WGL_EXT_depth_float,WGL_EXT_display_color_table,WGL_EXT_extensions_string,WGL_EXT_framebuffer_sRGB,WGL_EXT_make_current_read,WGL_EXT_multisample,WGL_EXT_pbuffer,WGL_EXT_pixel_format,WGL_EXT_pixel_format_packed_float,WGL_EXT_swap_control,WGL_EXT_swap_control_tear,WGL_I3D_digital_video_control,WGL_I3D_gamma,WGL_I3D_genlock,WGL_I3D_image_buffer,WGL_I3D_swap_frame_lock,WGL_I3D_swap_frame_usage,WGL_NV_DX_interop,WGL_NV_DX_interop2,WGL_NV_copy_image,WGL_NV_delay_before_swap,WGL_NV_float_buffer,WGL_NV_gpu_affinity,WGL_NV_multigpu_context,WGL_NV_multisample_coverage,WGL_NV_present_video,WGL_NV_render_depth_texture,WGL_NV_render_texture_rectangle,WGL_NV_swap_group,WGL_NV_vertex_array_range,WGL_NV_video_capture,WGL_NV_video_output,WGL_OML_sync_control"
    Online:
        Too many extensions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad_wgl.h>

static void* get_proc(const char *namez);

#if defined(_WIN32) || defined(__CYGWIN__)
#ifndef _WINDOWS_
#undef APIENTRY
#endif
#include <windows.h>
static HMODULE libGL;

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;

#ifdef _MSC_VER
#ifdef __has_include
  #if __has_include(<winapifamily.h>)
    #define HAVE_WINAPIFAMILY 1
  #endif
#elif _MSC_VER >= 1700 && !_USING_V110_SDK71_
  #define HAVE_WINAPIFAMILY 1
#endif
#endif

#ifdef HAVE_WINAPIFAMILY
  #include <winapifamily.h>
  #if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
    #define IS_UWP 1
  #endif
#endif

static
int open_wgl(void) {
#ifndef IS_UWP
    libGL = LoadLibraryW(L"opengl32.dll");
    if(libGL != NULL) {
        void (* tmp)(void);
        tmp = (void(*)(void)) GetProcAddress(libGL, "wglGetProcAddress");
        gladGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE) tmp;
        return gladGetProcAddressPtr != NULL;
    }
#endif

    return 0;
}

static
void close_wgl(void) {
    if(libGL != NULL) {
        FreeLibrary((HMODULE) libGL);
        libGL = NULL;
    }
}
#else
#include <dlfcn.h>
static void* libGL;

#if !defined(__APPLE__) && !defined(__HAIKU__)
typedef void* (APIENTRYP PFNGLXGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNGLXGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;
#endif

static
int open_wgl(void) {
#ifdef __APPLE__
    static const char *NAMES[] = {
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
    };
#else
    static const char *NAMES[] = {"libGL.so.1", "libGL.so"};
#endif

    unsigned int index = 0;
    for(index = 0; index < (sizeof(NAMES) / sizeof(NAMES[0])); index++) {
        libGL = dlopen(NAMES[index], RTLD_NOW | RTLD_GLOBAL);

        if(libGL != NULL) {
#if defined(__APPLE__) || defined(__HAIKU__)
            return 1;
#else
            gladGetProcAddressPtr = (PFNGLXGETPROCADDRESSPROC_PRIVATE)dlsym(libGL,
                "glXGetProcAddressARB");
            return gladGetProcAddressPtr != NULL;
#endif
        }
    }

    return 0;
}

static
void close_wgl(void) {
    if(libGL != NULL) {
        dlclose(libGL);
        libGL = NULL;
    }
}
#endif

static
void* get_proc(const char *namez) {
    void* result = NULL;
    if(libGL == NULL) return NULL;

#if !defined(__APPLE__) && !defined(__HAIKU__)
    if(gladGetProcAddressPtr != NULL) {
        result = gladGetProcAddressPtr(namez);
    }
#endif
    if(result == NULL) {
#if defined(_WIN32) || defined(__CYGWIN__)
        result = (void*)GetProcAddress((HMODULE) libGL, namez);
#else
        result = dlsym(libGL, namez);
#endif
    }

    return result;
}

int gladLoadWGL(HDC hdc) {
    int status = 0;

    if(open_wgl()) {
        status = gladLoadWGLLoader((GLADloadproc)get_proc, hdc);
    }

    return status;
}

void gladUnloadWGL(void) {
    close_wgl();
}

static HDC GLADWGLhdc = (HDC)INVALID_HANDLE_VALUE;

static int get_exts(void) {
    return 1;
}

static void free_exts(void) {
    return;
}

static int has_ext(const char *ext) {
    const char *terminator;
    const char *loc;
    const char *extensions;

    if(wglGetExtensionsStringEXT == NULL && wglGetExtensionsStringARB == NULL)
        return 0;

    if(wglGetExtensionsStringARB == NULL || GLADWGLhdc == INVALID_HANDLE_VALUE)
        extensions = wglGetExtensionsStringEXT();
    else
        extensions = wglGetExtensionsStringARB(GLADWGLhdc);

    if(extensions == NULL || ext == NULL)
        return 0;

    while(1) {
        loc = strstr(extensions, ext);
        if(loc == NULL)
            break;

        terminator = loc + strlen(ext);
        if((loc == extensions || *(loc - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0'))
        {
            return 1;
        }
        extensions = terminator;
    }

    return 0;
}
int GLAD_WGL_VERSION_1_0 = 0;
int GLAD_WGL_3DFX_multisample = 0;
int GLAD_WGL_3DL_stereo_control = 0;
int GLAD_WGL_AMD_gpu_association = 0;
int GLAD_WGL_ARB_buffer_region = 0;
int GLAD_WGL_ARB_context_flush_control = 0;
int GLAD_WGL_ARB_create_context = 0;
int GLAD_WGL_ARB_create_context_no_error = 0;
int GLAD_WGL_ARB_create_context_profile = 0;
int GLAD_WGL_ARB_create_context_robustness = 0;
int GLAD_WGL_ARB_extensions_string = 0;
int GLAD_WGL_ARB_framebuffer_sRGB = 0;
int GLAD_WGL_ARB_make_current_read = 0;
int GLAD_WGL_ARB_multisample = 0;
int GLAD_WGL_ARB_pbuffer = 0;
int GLAD_WGL_ARB_pixel_format = 0;
int GLAD_WGL_ARB_pixel_format_float = 0;
int GLAD_WGL_ARB_render_texture = 0;
int GLAD_WGL_ARB_robustness_application_isolation = 0;
int GLAD_WGL_ARB_robustness_share_group_isolation = 0;
int GLAD_WGL_ATI_pixel_format_float = 0;
int GLAD_WGL_ATI_render_texture_rectangle = 0;
int GLAD_WGL_EXT_colorspace = 0;
int GLAD_WGL_EXT_create_context_es2_profile = 0;
int GLAD_WGL_EXT_create_context_es_profile = 0;
int GLAD_WGL_EXT_depth_float = 0;
int GLAD_WGL_EXT_display_color_table = 0;
int GLAD_WGL_EXT_extensions_string = 0;
int GLAD_WGL_EXT_framebuffer_sRGB = 0;
int GLAD_WGL_EXT_make_current_read = 0;
int GLAD_WGL_EXT_multisample = 0;
int GLAD_WGL_EXT_pbuffer = 0;
int GLAD_WGL_EXT_pixel_format = 0;
int GLAD_WGL_EXT_pixel_format_packed_float = 0;
int GLAD_WGL_EXT_swap_control = 0;
int GLAD_WGL_EXT_swap_control_tear = 0;
int GLAD_WGL_I3D_digital_video_control = 0;
int GLAD_WGL_I3D_gamma = 0;
int GLAD_WGL_I3D_genlock = 0;
int GLAD_WGL_I3D_image_buffer = 0;
int GLAD_WGL_I3D_swap_frame_lock = 0;
int GLAD_WGL_I3D_swap_frame_usage = 0;
int GLAD_WGL_NV_DX_interop = 0;
int GLAD_WGL_NV_DX_interop2 = 0;
int GLAD_WGL_NV_copy_image = 0;
int GLAD_WGL_NV_delay_before_swap = 0;
int GLAD_WGL_NV_float_buffer = 0;
int GLAD_WGL_NV_gpu_affinity = 0;
int GLAD_WGL_NV_multigpu_context = 0;
int GLAD_WGL_NV_multisample_coverage = 0;
int GLAD_WGL_NV_present_video = 0;
int GLAD_WGL_NV_render_depth_texture = 0;
int GLAD_WGL_NV_render_texture_rectangle = 0;
int GLAD_WGL_NV_swap_group = 0;
int GLAD_WGL_NV_vertex_array_range = 0;
int GLAD_WGL_NV_video_capture = 0;
int GLAD_WGL_NV_video_output = 0;
int GLAD_WGL_OML_sync_control = 0;
PFNWGLSETSTEREOEMITTERSTATE3DLPROC glad_wglSetStereoEmitterState3DL = NULL;
PFNWGLGETGPUIDSAMDPROC glad_wglGetGPUIDsAMD = NULL;
PFNWGLGETGPUINFOAMDPROC glad_wglGetGPUInfoAMD = NULL;
PFNWGLGETCONTEXTGPUIDAMDPROC glad_wglGetContextGPUIDAMD = NULL;
PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC glad_wglCreateAssociatedContextAMD = NULL;
PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC glad_wglCreateAssociatedContextAttribsAMD = NULL;
PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC glad_wglDeleteAssociatedContextAMD = NULL;
PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC glad_wglMakeAssociatedContextCurrentAMD = NULL;
PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC glad_wglGetCurrentAssociatedContextAMD = NULL;
PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC glad_wglBlitContextFramebufferAMD = NULL;
PFNWGLCREATEBUFFERREGIONARBPROC glad_wglCreateBufferRegionARB = NULL;
PFNWGLDELETEBUFFERREGIONARBPROC glad_wglDeleteBufferRegionARB = NULL;
PFNWGLSAVEBUFFERREGIONARBPROC glad_wglSaveBufferRegionARB = NULL;
PFNWGLRESTOREBUFFERREGIONARBPROC glad_wglRestoreBufferRegionARB = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC glad_wglCreateContextAttribsARB = NULL;
PFNWGLGETEXTENSIONSSTRINGARBPROC glad_wglGetExtensionsStringARB = NULL;
PFNWGLMAKECONTEXTCURRENTARBPROC glad_wglMakeContextCurrentARB = NULL;
PFNWGLGETCURRENTREADDCARBPROC glad_wglGetCurrentReadDCARB = NULL;
PFNWGLCREATEPBUFFERARBPROC glad_wglCreatePbufferARB = NULL;
PFNWGLGETPBUFFERDCARBPROC glad_wglGetPbufferDCARB = NULL;
PFNWGLRELEASEPBUFFERDCARBPROC glad_wglReleasePbufferDCARB = NULL;
PFNWGLDESTROYPBUFFERARBPROC glad_wglDestroyPbufferARB = NULL;
PFNWGLQUERYPBUFFERARBPROC glad_wglQueryPbufferARB = NULL;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC glad_wglGetPixelFormatAttribivARB = NULL;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC glad_wglGetPixelFormatAttribfvARB = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC glad_wglChoosePixelFormatARB = NULL;
PFNWGLBINDTEXIMAGEARBPROC glad_wglBindTexImageARB = NULL;
PFNWGLRELEASETEXIMAGEARBPROC glad_wglReleaseTexImageARB = NULL;
PFNWGLSETPBUFFERATTRIBARBPROC glad_wglSetPbufferAttribARB = NULL;
PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC glad_wglCreateDisplayColorTableEXT = NULL;
PFNWGLLOADDISPLAYCOLORTABLEEXTPROC glad_wglLoadDisplayColorTableEXT = NULL;
PFNWGLBINDDISPLAYCOLORTABLEEXTPROC glad_wglBindDisplayColorTableEXT = NULL;
PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC glad_wglDestroyDisplayColorTableEXT = NULL;
PFNWGLGETEXTENSIONSSTRINGEXTPROC glad_wglGetExtensionsStringEXT = NULL;
PFNWGLMAKECONTEXTCURRENTEXTPROC glad_wglMakeContextCurrentEXT = NULL;
PFNWGLGETCURRENTREADDCEXTPROC glad_wglGetCurrentReadDCEXT = NULL;
PFNWGLCREATEPBUFFEREXTPROC glad_wglCreatePbufferEXT = NULL;
PFNWGLGETPBUFFERDCEXTPROC glad_wglGetPbufferDCEXT = NULL;
PFNWGLRELEASEPBUFFERDCEXTPROC glad_wglReleasePbufferDCEXT = NULL;
PFNWGLDESTROYPBUFFEREXTPROC glad_wglDestroyPbufferEXT = NULL;
PFNWGLQUERYPBUFFEREXTPROC glad_wglQueryPbufferEXT = NULL;
PFNWGLGETPIXELFORMATATTRIBIVEXTPROC glad_wglGetPixelFormatAttribivEXT = NULL;
PFNWGLGETPIXELFORMATATTRIBFVEXTPROC glad_wglGetPixelFormatAttribfvEXT = NULL;
PFNWGLCHOOSEPIXELFORMATEXTPROC glad_wglChoosePixelFormatEXT = NULL;
PFNWGLSWAPINTERVALEXTPROC glad_wglSwapIntervalEXT = NULL;
PFNWGLGETSWAPINTERVALEXTPROC glad_wglGetSwapIntervalEXT = NULL;
PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC glad_wglGetDigitalVideoParametersI3D = NULL;
PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC glad_wglSetDigitalVideoParametersI3D = NULL;
PFNWGLGETGAMMATABLEPARAMETERSI3DPROC glad_wglGetGammaTableParametersI3D = NULL;
PFNWGLSETGAMMATABLEPARAMETERSI3DPROC glad_wglSetGammaTableParametersI3D = NULL;
PFNWGLGETGAMMATABLEI3DPROC glad_wglGetGammaTableI3D = NULL;
PFNWGLSETGAMMATABLEI3DPROC glad_wglSetGammaTableI3D = NULL;
PFNWGLENABLEGENLOCKI3DPROC glad_wglEnableGenlockI3D = NULL;
PFNWGLDISABLEGENLOCKI3DPROC glad_wglDisableGenlockI3D = NULL;
PFNWGLISENABLEDGENLOCKI3DPROC glad_wglIsEnabledGenlockI3D = NULL;
PFNWGLGENLOCKSOURCEI3DPROC glad_wglGenlockSourceI3D = NULL;
PFNWGLGETGENLOCKSOURCEI3DPROC glad_wglGetGenlockSourceI3D = NULL;
PFNWGLGENLOCKSOURCEEDGEI3DPROC glad_wglGenlockSourceEdgeI3D = NULL;
PFNWGLGETGENLOCKSOURCEEDGEI3DPROC glad_wglGetGenlockSourceEdgeI3D = NULL;
PFNWGLGENLOCKSAMPLERATEI3DPROC glad_wglGenlockSampleRateI3D = NULL;
PFNWGLGETGENLOCKSAMPLERATEI3DPROC glad_wglGetGenlockSampleRateI3D = NULL;
PFNWGLGENLOCKSOURCEDELAYI3DPROC glad_wglGenlockSourceDelayI3D = NULL;
PFNWGLGETGENLOCKSOURCEDELAYI3DPROC glad_wglGetGenlockSourceDelayI3D = NULL;
PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC glad_wglQueryGenlockMaxSourceDelayI3D = NULL;
PFNWGLCREATEIMAGEBUFFERI3DPROC glad_wglCreateImageBufferI3D = NULL;
PFNWGLDESTROYIMAGEBUFFERI3DPROC glad_wglDestroyImageBufferI3D = NULL;
PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC glad_wglAssociateImageBufferEventsI3D = NULL;
PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC glad_wglReleaseImageBufferEventsI3D = NULL;
PFNWGLENABLEFRAMELOCKI3DPROC glad_wglEnableFrameLockI3D = NULL;
PFNWGLDISABLEFRAMELOCKI3DPROC glad_wglDisableFrameLockI3D = NULL;
PFNWGLISENABLEDFRAMELOCKI3DPROC glad_wglIsEnabledFrameLockI3D = NULL;
PFNWGLQUERYFRAMELOCKMASTERI3DPROC glad_wglQueryFrameLockMasterI3D = NULL;
PFNWGLGETFRAMEUSAGEI3DPROC glad_wglGetFrameUsageI3D = NULL;
PFNWGLBEGINFRAMETRACKINGI3DPROC glad_wglBeginFrameTrackingI3D = NULL;
PFNWGLENDFRAMETRACKINGI3DPROC glad_wglEndFrameTrackingI3D = NULL;
PFNWGLQUERYFRAMETRACKINGI3DPROC glad_wglQueryFrameTrackingI3D = NULL;
PFNWGLDXSETRESOURCESHAREHANDLENVPROC glad_wglDXSetResourceShareHandleNV = NULL;
PFNWGLDXOPENDEVICENVPROC glad_wglDXOpenDeviceNV = NULL;
PFNWGLDXCLOSEDEVICENVPROC glad_wglDXCloseDeviceNV = NULL;
PFNWGLDXREGISTEROBJECTNVPROC glad_wglDXRegisterObjectNV = NULL;
PFNWGLDXUNREGISTEROBJECTNVPROC glad_wglDXUnregisterObjectNV = NULL;
PFNWGLDXOBJECTACCESSNVPROC glad_wglDXObjectAccessNV = NULL;
PFNWGLDXLOCKOBJECTSNVPROC glad_wglDXLockObjectsNV = NULL;
PFNWGLDXUNLOCKOBJECTSNVPROC glad_wglDXUnlockObjectsNV = NULL;
PFNWGLCOPYIMAGESUBDATANVPROC glad_wglCopyImageSubDataNV = NULL;
PFNWGLDELAYBEFORESWAPNVPROC glad_wglDelayBeforeSwapNV = NULL;
PFNWGLENUMGPUSNVPROC glad_wglEnumGpusNV = NULL;
PFNWGLENUMGPUDEVICESNVPROC glad_wglEnumGpuDevicesNV = NULL;
PFNWGLCREATEAFFINITYDCNVPROC glad_wglCreateAffinityDCNV = NULL;
PFNWGLENUMGPUSFROMAFFINITYDCNVPROC glad_wglEnumGpusFromAffinityDCNV = NULL;
PFNWGLDELETEDCNVPROC glad_wglDeleteDCNV = NULL;
PFNWGLENUMERATEVIDEODEVICESNVPROC glad_wglEnumerateVideoDevicesNV = NULL;
PFNWGLBINDVIDEODEVICENVPROC glad_wglBindVideoDeviceNV = NULL;
PFNWGLQUERYCURRENTCONTEXTNVPROC glad_wglQueryCurrentContextNV = NULL;
PFNWGLJOINSWAPGROUPNVPROC glad_wglJoinSwapGroupNV = NULL;
PFNWGLBINDSWAPBARRIERNVPROC glad_wglBindSwapBarrierNV = NULL;
PFNWGLQUERYSWAPGROUPNVPROC glad_wglQuerySwapGroupNV = NULL;
PFNWGLQUERYMAXSWAPGROUPSNVPROC glad_wglQueryMaxSwapGroupsNV = NULL;
PFNWGLQUERYFRAMECOUNTNVPROC glad_wglQueryFrameCountNV = NULL;
PFNWGLRESETFRAMECOUNTNVPROC glad_wglResetFrameCountNV = NULL;
PFNWGLALLOCATEMEMORYNVPROC glad_wglAllocateMemoryNV = NULL;
PFNWGLFREEMEMORYNVPROC glad_wglFreeMemoryNV = NULL;
PFNWGLBINDVIDEOCAPTUREDEVICENVPROC glad_wglBindVideoCaptureDeviceNV = NULL;
PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC glad_wglEnumerateVideoCaptureDevicesNV = NULL;
PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC glad_wglLockVideoCaptureDeviceNV = NULL;
PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC glad_wglQueryVideoCaptureDeviceNV = NULL;
PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC glad_wglReleaseVideoCaptureDeviceNV = NULL;
PFNWGLGETVIDEODEVICENVPROC glad_wglGetVideoDeviceNV = NULL;
PFNWGLRELEASEVIDEODEVICENVPROC glad_wglReleaseVideoDeviceNV = NULL;
PFNWGLBINDVIDEOIMAGENVPROC glad_wglBindVideoImageNV = NULL;
PFNWGLRELEASEVIDEOIMAGENVPROC glad_wglReleaseVideoImageNV = NULL;
PFNWGLSENDPBUFFERTOVIDEONVPROC glad_wglSendPbufferToVideoNV = NULL;
PFNWGLGETVIDEOINFONVPROC glad_wglGetVideoInfoNV = NULL;
PFNWGLGETSYNCVALUESOMLPROC glad_wglGetSyncValuesOML = NULL;
PFNWGLGETMSCRATEOMLPROC glad_wglGetMscRateOML = NULL;
PFNWGLSWAPBUFFERSMSCOMLPROC glad_wglSwapBuffersMscOML = NULL;
PFNWGLSWAPLAYERBUFFERSMSCOMLPROC glad_wglSwapLayerBuffersMscOML = NULL;
PFNWGLWAITFORMSCOMLPROC glad_wglWaitForMscOML = NULL;
PFNWGLWAITFORSBCOMLPROC glad_wglWaitForSbcOML = NULL;
static void load_WGL_3DL_stereo_control(GLADloadproc load) {
	if(!GLAD_WGL_3DL_stereo_control) return;
	glad_wglSetStereoEmitterState3DL = (PFNWGLSETSTEREOEMITTERSTATE3DLPROC)load("wglSetStereoEmitterState3DL");
}
static void load_WGL_AMD_gpu_association(GLADloadproc load) {
	if(!GLAD_WGL_AMD_gpu_association) return;
	glad_wglGetGPUIDsAMD = (PFNWGLGETGPUIDSAMDPROC)load("wglGetGPUIDsAMD");
	glad_wglGetGPUInfoAMD = (PFNWGLGETGPUINFOAMDPROC)load("wglGetGPUInfoAMD");
	glad_wglGetContextGPUIDAMD = (PFNWGLGETCONTEXTGPUIDAMDPROC)load("wglGetContextGPUIDAMD");
	glad_wglCreateAssociatedContextAMD = (PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)load("wglCreateAssociatedContextAMD");
	glad_wglCreateAssociatedContextAttribsAMD = (PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)load("wglCreateAssociatedContextAttribsAMD");
	glad_wglDeleteAssociatedContextAMD = (PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)load("wglDeleteAssociatedContextAMD");
	glad_wglMakeAssociatedContextCurrentAMD = (PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)load("wglMakeAssociatedContextCurrentAMD");
	glad_wglGetCurrentAssociatedContextAMD = (PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)load("wglGetCurrentAssociatedContextAMD");
	glad_wglBlitContextFramebufferAMD = (PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)load("wglBlitContextFramebufferAMD");
}
static void load_WGL_ARB_buffer_region(GLADloadproc load) {
	if(!GLAD_WGL_ARB_buffer_region) return;
	glad_wglCreateBufferRegionARB = (PFNWGLCREATEBUFFERREGIONARBPROC)load("wglCreateBufferRegionARB");
	glad_wglDeleteBufferRegionARB = (PFNWGLDELETEBUFFERREGIONARBPROC)load("wglDeleteBufferRegionARB");
	glad_wglSaveBufferRegionARB = (PFNWGLSAVEBUFFERREGIONARBPROC)load("wglSaveBufferRegionARB");
	glad_wglRestoreBufferRegionARB = (PFNWGLRESTOREBUFFERREGIONARBPROC)load("wglRestoreBufferRegionARB");
}
static void load_WGL_ARB_create_context(GLADloadproc load) {
	if(!GLAD_WGL_ARB_create_context) return;
	glad_wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)load("wglCreateContextAttribsARB");
}
static void load_WGL_ARB_extensions_string(GLADloadproc load) {
	if(!GLAD_WGL_ARB_extensions_string) return;
	glad_wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)load("wglGetExtensionsStringARB");
}
static void load_WGL_ARB_make_current_read(GLADloadproc load) {
	if(!GLAD_WGL_ARB_make_current_read) return;
	glad_wglMakeContextCurrentARB = (PFNWGLMAKECONTEXTCURRENTARBPROC)load("wglMakeContextCurrentARB");
	glad_wglGetCurrentReadDCARB = (PFNWGLGETCURRENTREADDCARBPROC)load("wglGetCurrentReadDCARB");
}
static void load_WGL_ARB_pbuffer(GLADloadproc load) {
	if(!GLAD_WGL_ARB_pbuffer) return;
	glad_wglCreatePbufferARB = (PFNWGLCREATEPBUFFERARBPROC)load("wglCreatePbufferARB");
	glad_wglGetPbufferDCARB = (PFNWGLGETPBUFFERDCARBPROC)load("wglGetPbufferDCARB");
	glad_wglReleasePbufferDCARB = (PFNWGLRELEASEPBUFFERDCARBPROC)load("wglReleasePbufferDCARB");
	glad_wglDestroyPbufferARB = (PFNWGLDESTROYPBUFFERARBPROC)load("wglDestroyPbufferARB");
	glad_wglQueryPbufferARB = (PFNWGLQUERYPBUFFERARBPROC)load("wglQueryPbufferARB");
}
static void load_WGL_ARB_pixel_format(GLADloadproc load) {
	if(!GLAD_WGL_ARB_pixel_format) return;
	glad_wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)load("wglGetPixelFormatAttribivARB");
	glad_wglGetPixelFormatAttribfvARB = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)load("wglGetPixelFormatAttribfvARB");
	glad_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)load("wglChoosePixelFormatARB");
}
static void load_WGL_ARB_render_texture(GLADloadproc load) {
	if(!GLAD_WGL_ARB_render_texture) return;
	glad_wglBindTexImageARB = (PFNWGLBINDTEXIMAGEARBPROC)load("wglBindTexImageARB");
	glad_wglReleaseTexImageARB = (PFNWGLRELEASETEXIMAGEARBPROC)load("wglReleaseTexImageARB");
	glad_wglSetPbufferAttribARB = (PFNWGLSETPBUFFERATTRIBARBPROC)load("wglSetPbufferAttribARB");
}
static void load_WGL_EXT_display_color_table(GLADloadproc load) {
	if(!GLAD_WGL_EXT_display_color_table) return;
	glad_wglCreateDisplayColorTableEXT = (PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC)load("wglCreateDisplayColorTableEXT");
	glad_wglLoadDisplayColorTableEXT = (PFNWGLLOADDISPLAYCOLORTABLEEXTPROC)load("wglLoadDisplayColorTableEXT");
	glad_wglBindDisplayColorTableEXT = (PFNWGLBINDDISPLAYCOLORTABLEEXTPROC)load("wglBindDisplayColorTableEXT");
	glad_wglDestroyDisplayColorTableEXT = (PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC)load("wglDestroyDisplayColorTableEXT");
}
static void load_WGL_EXT_extensions_string(GLADloadproc load) {
	if(!GLAD_WGL_EXT_extensions_string) return;
	glad_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)load("wglGetExtensionsStringEXT");
}
static void load_WGL_EXT_make_current_read(GLADloadproc load) {
	if(!GLAD_WGL_EXT_make_current_read) return;
	glad_wglMakeContextCurrentEXT = (PFNWGLMAKECONTEXTCURRENTEXTPROC)load("wglMakeContextCurrentEXT");
	glad_wglGetCurrentReadDCEXT = (PFNWGLGETCURRENTREADDCEXTPROC)load("wglGetCurrentReadDCEXT");
}
static void load_WGL_EXT_pbuffer(GLADloadproc load) {
	if(!GLAD_WGL_EXT_pbuffer) return;
	glad_wglCreatePbufferEXT = (PFNWGLCREATEPBUFFEREXTPROC)load("wglCreatePbufferEXT");
	glad_wglGetPbufferDCEXT = (PFNWGLGETPBUFFERDCEXTPROC)load("wglGetPbufferDCEXT");
	glad_wglReleasePbufferDCEXT = (PFNWGLRELEASEPBUFFERDCEXTPROC)load("wglReleasePbufferDCEXT");
	glad_wglDestroyPbufferEXT = (PFNWGLDESTROYPBUFFEREXTPROC)load("wglDestroyPbufferEXT");
	glad_wglQueryPbufferEXT = (PFNWGLQUERYPBUFFEREXTPROC)load("wglQueryPbufferEXT");
}
static void load_WGL_EXT_pixel_format(GLADloadproc load) {
	if(!GLAD_WGL_EXT_pixel_format) return;
	glad_wglGetPixelFormatAttribivEXT = (PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)load("wglGetPixelFormatAttribivEXT");
	glad_wglGetPixelFormatAttribfvEXT = (PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)load("wglGetPixelFormatAttribfvEXT");
	glad_wglChoosePixelFormatEXT = (PFNWGLCHOOSEPIXELFORMATEXTPROC)load("wglChoosePixelFormatEXT");
}
static void load_WGL_EXT_swap_control(GLADloadproc load) {
	if(!GLAD_WGL_EXT_swap_control) return;
	glad_wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)load("wglSwapIntervalEXT");
	glad_wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)load("wglGetSwapIntervalEXT");
}
static void load_WGL_I3D_digital_video_control(GLADloadproc load) {
	if(!GLAD_WGL_I3D_digital_video_control) return;
	glad_wglGetDigitalVideoParametersI3D = (PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC)load("wglGetDigitalVideoParametersI3D");
	glad_wglSetDigitalVideoParametersI3D = (PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC)load("wglSetDigitalVideoParametersI3D");
}
static void load_WGL_I3D_gamma(GLADloadproc load) {
	if(!GLAD_WGL_I3D_gamma) return;
	glad_wglGetGammaTableParametersI3D = (PFNWGLGETGAMMATABLEPARAMETERSI3DPROC)load("wglGetGammaTableParametersI3D");
	glad_wglSetGammaTableParametersI3D = (PFNWGLSETGAMMATABLEPARAMETERSI3DPROC)load("wglSetGammaTableParametersI3D");
	glad_wglGetGammaTableI3D = (PFNWGLGETGAMMATABLEI3DPROC)load("wglGetGammaTableI3D");
	glad_wglSetGammaTableI3D = (PFNWGLSETGAMMATABLEI3DPROC)load("wglSetGammaTableI3D");
}
static void load_WGL_I3D_genlock(GLADloadproc load) {
	if(!GLAD_WGL_I3D_genlock) return;
	glad_wglEnableGenlockI3D = (PFNWGLENABLEGENLOCKI3DPROC)load("wglEnableGenlockI3D");
	glad_wglDisableGenlockI3D = (PFNWGLDISABLEGENLOCKI3DPROC)load("wglDisableGenlockI3D");
	glad_wglIsEnabledGenlockI3D = (PFNWGLISENABLEDGENLOCKI3DPROC)load("wglIsEnabledGenlockI3D");
	glad_wglGenlockSourceI3D = (PFNWGLGENLOCKSOURCEI3DPROC)load("wglGenlockSourceI3D");
	glad_wglGetGenlockSourceI3D = (PFNWGLGETGENLOCKSOURCEI3DPROC)load("wglGetGenlockSourceI3D");
	glad_wglGenlockSourceEdgeI3D = (PFNWGLGENLOCKSOURCEEDGEI3DPROC)load("wglGenlockSourceEdgeI3D");
	glad_wglGetGenlockSourceEdgeI3D = (PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)load("wglGetGenlockSourceEdgeI3D");
	glad_wglGenlockSampleRateI3D = (PFNWGLGENLOCKSAMPLERATEI3DPROC)load("wglGenlockSampleRateI3D");
	glad_wglGetGenlockSampleRateI3D = (PFNWGLGETGENLOCKSAMPLERATEI3DPROC)load("wglGetGenlockSampleRateI3D");
	glad_wglGenlockSourceDelayI3D = (PFNWGLGENLOCKSOURCEDELAYI3DPROC)load("wglGenlockSourceDelayI3D");
	glad_wglGetGenlockSourceDelayI3D = (PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)load("wglGetGenlockSourceDelayI3D");
	glad_wglQueryGenlockMaxSourceDelayI3D = (PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)load("wglQueryGenlockMaxSourceDelayI3D");
}
static void load_WGL_I3D_image_buffer(GLADloadproc load) {
	if(!GLAD_WGL_I3D_image_buffer) return;
	glad_wglCreateImageBufferI3D = (PFNWGLCREATEIMAGEBUFFERI3DPROC)load("wglCreateImageBufferI3D");
	glad_wglDestroyImageBufferI3D = (PFNWGLDESTROYIMAGEBUFFERI3DPROC)load("wglDestroyImageBufferI3D");
	glad_wglAssociateImageBufferEventsI3D = (PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC)load("wglAssociateImageBufferEventsI3D");
	glad_wglReleaseImageBufferEventsI3D = (PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC)load("wglReleaseImageBufferEventsI3D");
}
static void load_WGL_I3D_swap_frame_lock(GLADloadproc load) {
	if(!GLAD_WGL_I3D_swap_frame_lock) return;
	glad_wglEnableFrameLockI3D = (PFNWGLENABLEFRAMELOCKI3DPROC)load("wglEnableFrameLockI3D");
	glad_wglDisableFrameLockI3D = (PFNWGLDISABLEFRAMELOCKI3DPROC)load("wglDisableFrameLockI3D");
	glad_wglIsEnabledFrameLockI3D = (PFNWGLISENABLEDFRAMELOCKI3DPROC)load("wglIsEnabledFrameLockI3D");
	glad_wglQueryFrameLockMasterI3D = (PFNWGLQUERYFRAMELOCKMASTERI3DPROC)load("wglQueryFrameLockMasterI3D");
}
static void load_WGL_I3D_swap_frame_usage(GLADloadproc load) {
	if(!GLAD_WGL_I3D_swap_frame_usage) return;
	glad_wglGetFrameUsageI3D = (PFNWGLGETFRAMEUSAGEI3DPROC)load("wglGetFrameUsageI3D");
	glad_wglBeginFrameTrackingI3D = (PFNWGLBEGINFRAMETRACKINGI3DPROC)load("wglBeginFrameTrackingI3D");
	glad_wglEndFrameTrackingI3D = (PFNWGLENDFRAMETRACKINGI3DPROC)load("wglEndFrameTrackingI3D");
	glad_wglQueryFrameTrackingI3D = (PFNWGLQUERYFRAMETRACKINGI3DPROC)load("wglQueryFrameTrackingI3D");
}
static void load_WGL_NV_DX_interop(GLADloadproc load) {
	if(!GLAD_WGL_NV_DX_interop) return;
	glad_wglDXSetResourceShareHandleNV = (PFNWGLDXSETRESOURCESHAREHANDLENVPROC)load("wglDXSetResourceShareHandleNV");
	glad_wglDXOpenDeviceNV = (PFNWGLDXOPENDEVICENVPROC)load("wglDXOpenDeviceNV");
	glad_wglDXCloseDeviceNV = (PFNWGLDXCLOSEDEVICENVPROC)load("wglDXCloseDeviceNV");
	glad_wglDXRegisterObjectNV = (PFNWGLDXREGISTEROBJECTNVPROC)load("wglDXRegisterObjectNV");
	glad_wglDXUnregisterObjectNV = (PFNWGLDXUNREGISTEROBJECTNVPROC)load("wglDXUnregisterObjectNV");
	glad_wglDXObjectAccessNV = (PFNWGLDXOBJECTACCESSNVPROC)load("wglDXObjectAccessNV");
	glad_wglDXLockObjectsNV = (PFNWGLDXLOCKOBJECTSNVPROC)load("wglDXLockObjectsNV");
	glad_wglDXUnlockObjectsNV = (PFNWGLDXUNLOCKOBJECTSNVPROC)load("wglDXUnlockObjectsNV");
}
static void load_WGL_NV_copy_image(GLADloadproc load) {
	if(!GLAD_WGL_NV_copy_image) return;
	glad_wglCopyImageSubDataNV = (PFNWGLCOPYIMAGESUBDATANVPROC)load("wglCopyImageSubDataNV");
}
static void load_WGL_NV_delay_before_swap(GLADloadproc load) {
	if(!GLAD_WGL_NV_delay_before_swap) return;
	glad_wglDelayBeforeSwapNV = (PFNWGLDELAYBEFORESWAPNVPROC)load("wglDelayBeforeSwapNV");
}
static void load_WGL_NV_gpu_affinity(GLADloadproc load) {
	if(!GLAD_WGL_NV_gpu_affinity) return;
	glad_wglEnumGpusNV = (PFNWGLENUMGPUSNVPROC)load("wglEnumGpusNV");
	glad_wglEnumGpuDevicesNV = (PFNWGLENUMGPUDEVICESNVPROC)load("wglEnumGpuDevicesNV");
	glad_wglCreateAffinityDCNV = (PFNWGLCREATEAFFINITYDCNVPROC)load("wglCreateAffinityDCNV");
	glad_wglEnumGpusFromAffinityDCNV = (PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)load("wglEnumGpusFromAffinityDCNV");
	glad_wglDeleteDCNV = (PFNWGLDELETEDCNVPROC)load("wglDeleteDCNV");
}
static void load_WGL_NV_present_video(GLADloadproc load) {
	if(!GLAD_WGL_NV_present_video) return;
	glad_wglEnumerateVideoDevicesNV = (PFNWGLENUMERATEVIDEODEVICESNVPROC)load("wglEnumerateVideoDevicesNV");
	glad_wglBindVideoDeviceNV = (PFNWGLBINDVIDEODEVICENVPROC)load("wglBindVideoDeviceNV");
	glad_wglQueryCurrentContextNV = (PFNWGLQUERYCURRENTCONTEXTNVPROC)load("wglQueryCurrentContextNV");
}
static void load_WGL_NV_swap_group(GLADloadproc load) {
	if(!GLAD_WGL_NV_swap_group) return;
	glad_wglJoinSwapGroupNV = (PFNWGLJOINSWAPGROUPNVPROC)load("wglJoinSwapGroupNV");
	glad_wglBindSwapBarrierNV = (PFNWGLBINDSWAPBARRIERNVPROC)load("wglBindSwapBarrierNV");
	glad_wglQuerySwapGroupNV = (PFNWGLQUERYSWAPGROUPNVPROC)load("wglQuerySwapGroupNV");
	glad_wglQueryMaxSwapGroupsNV = (PFNWGLQUERYMAXSWAPGROUPSNVPROC)load("wglQueryMaxSwapGroupsNV");
	glad_wglQueryFrameCountNV = (PFNWGLQUERYFRAMECOUNTNVPROC)load("wglQueryFrameCountNV");
	glad_wglResetFrameCountNV = (PFNWGLRESETFRAMECOUNTNVPROC)load("wglResetFrameCountNV");
}
static void load_WGL_NV_vertex_array_range(GLADloadproc load) {
	if(!GLAD_WGL_NV_vertex_array_range) return;
	glad_wglAllocateMemoryNV = (PFNWGLALLOCATEMEMORYNVPROC)load("wglAllocateMemoryNV");
	glad_wglFreeMemoryNV = (PFNWGLFREEMEMORYNVPROC)load("wglFreeMemoryNV");
}
static void load_WGL_NV_video_capture(GLADloadproc load) {
	if(!GLAD_WGL_NV_video_capture) return;
	glad_wglBindVideoCaptureDeviceNV = (PFNWGLBINDVIDEOCAPTUREDEVICENVPROC)load("wglBindVideoCaptureDeviceNV");
	glad_wglEnumerateVideoCaptureDevicesNV = (PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC)load("wglEnumerateVideoCaptureDevicesNV");
	glad_wglLockVideoCaptureDeviceNV = (PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC)load("wglLockVideoCaptureDeviceNV");
	glad_wglQueryVideoCaptureDeviceNV = (PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC)load("wglQueryVideoCaptureDeviceNV");
	glad_wglReleaseVideoCaptureDeviceNV = (PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC)load("wglReleaseVideoCaptureDeviceNV");
}
static void load_WGL_NV_video_output(GLADloadproc load) {
	if(!GLAD_WGL_NV_video_output) return;
	glad_wglGetVideoDeviceNV = (PFNWGLGETVIDEODEVICENVPROC)load("wglGetVideoDeviceNV");
	glad_wglReleaseVideoDeviceNV = (PFNWGLRELEASEVIDEODEVICENVPROC)load("wglReleaseVideoDeviceNV");
	glad_wglBindVideoImageNV = (PFNWGLBINDVIDEOIMAGENVPROC)load("wglBindVideoImageNV");
	glad_wglReleaseVideoImageNV = (PFNWGLRELEASEVIDEOIMAGENVPROC)load("wglReleaseVideoImageNV");
	glad_wglSendPbufferToVideoNV = (PFNWGLSENDPBUFFERTOVIDEONVPROC)load("wglSendPbufferToVideoNV");
	glad_wglGetVideoInfoNV = (PFNWGLGETVIDEOINFONVPROC)load("wglGetVideoInfoNV");
}
static void load_WGL_OML_sync_control(GLADloadproc load) {
	if(!GLAD_WGL_OML_sync_control) return;
	glad_wglGetSyncValuesOML = (PFNWGLGETSYNCVALUESOMLPROC)load("wglGetSyncValuesOML");
	glad_wglGetMscRateOML = (PFNWGLGETMSCRATEOMLPROC)load("wglGetMscRateOML");
	glad_wglSwapBuffersMscOML = (PFNWGLSWAPBUFFERSMSCOMLPROC)load("wglSwapBuffersMscOML");
	glad_wglSwapLayerBuffersMscOML = (PFNWGLSWAPLAYERBUFFERSMSCOMLPROC)load("wglSwapLayerBuffersMscOML");
	glad_wglWaitForMscOML = (PFNWGLWAITFORMSCOMLPROC)load("wglWaitForMscOML");
	glad_wglWaitForSbcOML = (PFNWGLWAITFORSBCOMLPROC)load("wglWaitForSbcOML");
}
static int find_extensionsWGL(void) {
	if (!get_exts()) return 0;
	GLAD_WGL_3DFX_multisample = has_ext("WGL_3DFX_multisample");
	GLAD_WGL_3DL_stereo_control = has_ext("WGL_3DL_stereo_control");
	GLAD_WGL_AMD_gpu_association = has_ext("WGL_AMD_gpu_association");
	GLAD_WGL_ARB_buffer_region = has_ext("WGL_ARB_buffer_region");
	GLAD_WGL_ARB_context_flush_control = has_ext("WGL_ARB_context_flush_control");
	GLAD_WGL_ARB_create_context = has_ext("WGL_ARB_create_context");
	GLAD_WGL_ARB_create_context_no_error = has_ext("WGL_ARB_create_context_no_error");
	GLAD_WGL_ARB_create_context_profile = has_ext("WGL_ARB_create_context_profile");
	GLAD_WGL_ARB_create_context_robustness = has_ext("WGL_ARB_create_context_robustness");
	GLAD_WGL_ARB_extensions_string = has_ext("WGL_ARB_extensions_string");
	GLAD_WGL_ARB_framebuffer_sRGB = has_ext("WGL_ARB_framebuffer_sRGB");
	GLAD_WGL_ARB_make_current_read = has_ext("WGL_ARB_make_current_read");
	GLAD_WGL_ARB_multisample = has_ext("WGL_ARB_multisample");
	GLAD_WGL_ARB_pbuffer = has_ext("WGL_ARB_pbuffer");
	GLAD_WGL_ARB_pixel_format = has_ext("WGL_ARB_pixel_format");
	GLAD_WGL_ARB_pixel_format_float = has_ext("WGL_ARB_pixel_format_float");
	GLAD_WGL_ARB_render_texture = has_ext("WGL_ARB_render_texture");
	GLAD_WGL_ARB_robustness_application_isolation = has_ext("WGL_ARB_robustness_application_isolation");
	GLAD_WGL_ARB_robustness_share_group_isolation = has_ext("WGL_ARB_robustness_share_group_isolation");
	GLAD_WGL_ATI_pixel_format_float = has_ext("WGL_ATI_pixel_format_float");
	GLAD_WGL_ATI_render_texture_rectangle = has_ext("WGL_ATI_render_texture_rectangle");
	GLAD_WGL_EXT_colorspace = has_ext("WGL_EXT_colorspace");
	GLAD_WGL_EXT_create_context_es2_profile = has_ext("WGL_EXT_create_context_es2_profile");
	GLAD_WGL_EXT_create_context_es_profile = has_ext("WGL_EXT_create_context_es_profile");
	GLAD_WGL_EXT_depth_float = has_ext("WGL_EXT_depth_float");
	GLAD_WGL_EXT_display_color_table = has_ext("WGL_EXT_display_color_table");
	GLAD_WGL_EXT_extensions_string = has_ext("WGL_EXT_extensions_string");
	GLAD_WGL_EXT_framebuffer_sRGB = has_ext("WGL_EXT_framebuffer_sRGB");
	GLAD_WGL_EXT_make_current_read = has_ext("WGL_EXT_make_current_read");
	GLAD_WGL_EXT_multisample = has_ext("WGL_EXT_multisample");
	GLAD_WGL_EXT_pbuffer = has_ext("WGL_EXT_pbuffer");
	GLAD_WGL_EXT_pixel_format = has_ext("WGL_EXT_pixel_format");
	GLAD_WGL_EXT_pixel_format_packed_float = has_ext("WGL_EXT_pixel_format_packed_float");
	GLAD_WGL_EXT_swap_control = has_ext("WGL_EXT_swap_control");
	GLAD_WGL_EXT_swap_control_tear = has_ext("WGL_EXT_swap_control_tear");
	GLAD_WGL_I3D_digital_video_control = has_ext("WGL_I3D_digital_video_control");
	GLAD_WGL_I3D_gamma = has_ext("WGL_I3D_gamma");
	GLAD_WGL_I3D_genlock = has_ext("WGL_I3D_genlock");
	GLAD_WGL_I3D_image_buffer = has_ext("WGL_I3D_image_buffer");
	GLAD_WGL_I3D_swap_frame_lock = has_ext("WGL_I3D_swap_frame_lock");
	GLAD_WGL_I3D_swap_frame_usage = has_ext("WGL_I3D_swap_frame_usage");
	GLAD_WGL_NV_DX_interop = has_ext("WGL_NV_DX_interop");
	GLAD_WGL_NV_DX_interop2 = has_ext("WGL_NV_DX_interop2");
	GLAD_WGL_NV_copy_image = has_ext("WGL_NV_copy_image");
	GLAD_WGL_NV_delay_before_swap = has_ext("WGL_NV_delay_before_swap");
	GLAD_WGL_NV_float_buffer = has_ext("WGL_NV_float_buffer");
	GLAD_WGL_NV_gpu_affinity = has_ext("WGL_NV_gpu_affinity");
	GLAD_WGL_NV_multigpu_context = has_ext("WGL_NV_multigpu_context");
	GLAD_WGL_NV_multisample_coverage = has_ext("WGL_NV_multisample_coverage");
	GLAD_WGL_NV_present_video = has_ext("WGL_NV_present_video");
	GLAD_WGL_NV_render_depth_texture = has_ext("WGL_NV_render_depth_texture");
	GLAD_WGL_NV_render_texture_rectangle = has_ext("WGL_NV_render_texture_rectangle");
	GLAD_WGL_NV_swap_group = has_ext("WGL_NV_swap_group");
	GLAD_WGL_NV_vertex_array_range = has_ext("WGL_NV_vertex_array_range");
	GLAD_WGL_NV_video_capture = has_ext("WGL_NV_video_capture");
	GLAD_WGL_NV_video_output = has_ext("WGL_NV_video_output");
	GLAD_WGL_OML_sync_control = has_ext("WGL_OML_sync_control");
	free_exts();
	return 1;
}

static void find_coreWGL(HDC hdc) {
	GLADWGLhdc = hdc;
}

int gladLoadWGLLoader(GLADloadproc load, HDC hdc) {
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)load("wglGetExtensionsStringARB");
	wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)load("wglGetExtensionsStringEXT");
	if(wglGetExtensionsStringARB == NULL && wglGetExtensionsStringEXT == NULL) return 0;
	find_coreWGL(hdc);

	if (!find_extensionsWGL()) return 0;
	load_WGL_3DL_stereo_control(load);
	load_WGL_AMD_gpu_association(load);
	load_WGL_ARB_buffer_region(load);
	load_WGL_ARB_create_context(load);
	load_WGL_ARB_extensions_string(load);
	load_WGL_ARB_make_current_read(load);
	load_WGL_ARB_pbuffer(load);
	load_WGL_ARB_pixel_format(load);
	load_WGL_ARB_render_texture(load);
	load_WGL_EXT_display_color_table(load);
	load_WGL_EXT_extensions_string(load);
	load_WGL_EXT_make_current_read(load);
	load_WGL_EXT_pbuffer(load);
	load_WGL_EXT_pixel_format(load);
	load_WGL_EXT_swap_control(load);
	load_WGL_I3D_digital_video_control(load);
	load_WGL_I3D_gamma(load);
	load_WGL_I3D_genlock(load);
	load_WGL_I3D_image_buffer(load);
	load_WGL_I3D_swap_frame_lock(load);
	load_WGL_I3D_swap_frame_usage(load);
	load_WGL_NV_DX_interop(load);
	load_WGL_NV_copy_image(load);
	load_WGL_NV_delay_before_swap(load);
	load_WGL_NV_gpu_affinity(load);
	load_WGL_NV_present_video(load);
	load_WGL_NV_swap_group(load);
	load_WGL_NV_vertex_array_range(load);
	load_WGL_NV_video_capture(load);
	load_WGL_NV_video_output(load);
	load_WGL_OML_sync_control(load);
	return 1;
}

