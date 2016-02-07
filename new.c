/*
 * new -- Create new file
 * Copyright (C) 2016 Jacob Adams <tookmund@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 3 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "perm.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("%s [filename]\n",argv[0]);
	}
	else {
		int fd = open(argv[1],O_CREAT | O_EXCL,MODE);
		if (fd < 0) {
			perror(argv[1]);
			return 1;
		}
		return 0;
	}
}
