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

#include <gpiod.h>
#include "../../tools/tools-common.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // TODO

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __GPIOD_CS_WRAPPER_H__ */