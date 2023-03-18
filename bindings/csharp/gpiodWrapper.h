#pragma once

#ifndef __GPIOD_CS_WRAPPER_H__
#define __GPIOD_CS_WRAPPER_H__

#ifdef __cplusplus
extern "C"
{
#endif

    int gpiodetect(char ***outPaths);
    int print_chip_info(const char *path);
    // EXPORT_CLASS_API int gpioget(char *path, int offset);
    // EXPORT_CLASS_API void gpioset(char *path, int offset, int value);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __GPIOD_CS_WRAPPER_H__ */