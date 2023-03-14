#include <gpiod.h>
#include <stdio.h>
#include <tools-common.h>
#include "gpiodWrapper.h"

static int print_chip_info(const char *path)
{
	struct gpiod_chip_info *info;
	struct gpiod_chip *chip;

	chip = gpiod_chip_open(path);
	if (!chip) {
		print_perror("unable to open chip '%s'", path);
		return 1;
	}

	info = gpiod_chip_get_info(chip);
	if (!info)
		die_perror("unable to read info for '%s'", path);

	printf("%s [%s] (%zu lines)\n", gpiod_chip_info_get_name(info),
	       gpiod_chip_info_get_label(info),
	       gpiod_chip_info_get_num_lines(info));

	gpiod_chip_info_free(info);
	gpiod_chip_close(chip);

	return 0;
}

static int add(float x, float y) {
	return (int)x + y;
}

static int gpiodetect() {

    int num_chips, i, ret = 0;
	char **paths;

	num_chips = all_chip_paths(&paths);
    for (i = 0; i < num_chips; i++) {
        if (print_chip_info(paths[i]))
            ret = -1;

		// free(paths[i]);
	}
	// free(paths);

	return num_chips;
}