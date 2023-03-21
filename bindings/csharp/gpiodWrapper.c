#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <tools-common.h>
#include "gpiodWrapper.h"
#include <android/log.h>

#define LOG_TAG "gpiod"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static void log_line_info(int offset, struct gpiod_line_info *info)
{
	const char *name = gpiod_line_info_get_name(info);
	LOGD("%d : %-16s\t%s", 
			offset,
			name ? name : "unnamed",
			gpiod_line_info_get_direction(info) == GPIOD_LINE_DIRECTION_INPUT ?  "input" : "output"
			);
	//
}

static int log_chip_info(const char *path, bool line_info)
{
	// open chip
	struct gpiod_chip *chip;
	chip = gpiod_chip_open(path);
	if (!chip) {
		LOGE("unable to open chip '%s'", path);
		return 1;
	}

	// get chip info
	struct gpiod_chip_info *chip_info;
	chip_info = gpiod_chip_get_info(chip);
	if (!chip_info)
		LOGE("unable to read info for '%s'", path);

	// log chip info
	LOGD("%s [%s] (%zu lines)\n", gpiod_chip_info_get_name(chip_info),
	       gpiod_chip_info_get_label(chip_info),
	       gpiod_chip_info_get_num_lines(chip_info));

	// log line info
	if (line_info) {
		// print all line name based on offset
		struct gpiod_line_info *info;
		for (int offset = 0; offset < gpiod_chip_info_get_num_lines(chip_info); offset++)
		{
			info = gpiod_chip_get_line_info(chip, offset);
			log_line_info(offset, info);
		}
		gpiod_line_info_free(info);
	}

	// free chip info
	gpiod_chip_info_free(chip_info);

	// close chip
	gpiod_chip_close(chip);

	return 0;
}

int gpiodetect(char ***outPaths) {

    int num_chips, i, ret = 0;
	char **paths;

	num_chips = all_chip_paths(&paths);
    for (i = 0; i < num_chips; i++) {
        if (log_chip_info(paths[i], false))
            ret = -1;
	}
	*outPaths = paths;

	return num_chips;
}

// int gpioget(char *path, int offset) {
// 	int ret = 0;
// 	struct gpiod_chip *chip;
// 	struct gpiod_line *line;
// 	struct gpiod_line_request_config config = {
// 		.consumer = "gpioget",
// 		.request_type = GPIOD_LINE_REQUEST_DIRECTION_INPUT,
// 	};

// 	chip = gpiod_chip_open(path);
// 	if (!chip) {
// 		LOGE("unable to open chip '%s'", path);
// 		return 1;
// 	}

// 	line = gpiod_chip_get_line(chip, offset);
// 	if (!line) {
// 		LOGE("unable to get line %d", offset);
// 		ret = 1;
// 		goto close_chip;
// 	}

// 	ret = gpiod_line_request(line, &config, 0);
// 	if (ret) {
// 		LOGE("unable to request line %d", offset);
// 		goto close_chip;
// 	}

// 	ret = gpiod_line_get_value(line);
// 	if (ret < 0) {
// 		LOGE("unable to read value from line %d", offset);
// 		goto release_line;
// 	}