#pragma once

#if defined( _WIN32 )
#ifdef viveport_ext_api_EXPORTS
#define VIVEPORT_EXT_API extern "C" __declspec(dllexport)
#else  // viveport_ext_api_EXPORTS
#define VIVEPORT_EXT_API extern "C" __declspec(dllimport)
#endif // viveport_ext_api_EXPORTS
#elif defined( __GNUC__ )
#define __cdecl    /* nothing */
#define __fastcall /* nothing */
#define __stdcall  /* nothing */
#ifdef viveport_ext_api_EXPORTS
#define VIVEPORT_EXT_API extern "C" __attribute__ ((visibility("default")))
#else  // viveport_ext_api_EXPORTS
#define VIVEPORT_EXT_API extern "C"
#endif // viveport_ext_api_EXPORTS
#else // !_WIN32
#define __cdecl    /* nothing */
#define __fastcall /* nothing */
#define __stdcall  /* nothing */
#ifdef viveport_ext_api_EXPORTS
#define VIVEPORT_EXT_API extern "C"
#else  // viveport_ext_api_EXPORTS
#define VIVEPORT_EXT_API extern "C"
#endif // viveport_ext_api_EXPORTS
#endif


/**
 * Top-level API
 */
struct IViveportExtApi
{
    virtual const char* Version() = 0;
};

VIVEPORT_EXT_API IViveportExtApi* ViveportExtApi();
VIVEPORT_EXT_API const char* IViveportExtApi_Version();

/**
 * License API
 */
struct IViveportExtLicense
{
    virtual int VerifyMessage(
            const char* app_id,
            const char* app_key,
            const char* message,
            const char* signature
    ) = 0;
};

VIVEPORT_EXT_API IViveportExtLicense* ViveportExtLicense();
VIVEPORT_EXT_API int IViveportExtLicense_VerifyMessage(
        const char* app_id,
        const char* app_key,
        const char* message,
        const char* signature
);
