#pragma once

#ifndef __GPIOD_CS_WRAPPER_H__
#define __GPIOD_CS_WRAPPER_H__

#ifdef WIN32
#ifdef DLL_EXPORTS
#define EXPORT_CLASS __declspec(dllexport)
#define EXPORT_API extern "C" __declspec(dllexport)
#define EXPORT_CLASS_API
#else
#define EXPORT_CLASS __declspec(dllimport)
#define EXPORT_API extern "C" __declspec(dllimport)
#define EXPORT_CLASS_API
#endif
#else
#define EXPORT_CLASS
#define EXPORT_API extern "C" __attribute__((visibility("default")))
#define EXPORT_CLASS_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    EXPORT_CLASS_API static int add(float x, float y);
    EXPORT_CLASS_API static int gpiodetect();
    // EXPORT_CLASS_API int gpioget(char *path, int offset);
    // EXPORT_CLASS_API void gpioset(char *path, int offset, int value);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __GPIOD_CS_WRAPPER_H__ */