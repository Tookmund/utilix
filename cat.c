/*
 * cat -- Concatenate files
 * Copyright (C) 2016 Jacob Adams <tookmund@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXBUF 1000

int main (int argc, char* argv[]) {
	int i;
	struct stat st;
	char* buf;
	int ret;
	int fd;
	int rd;
	int wr;
	char pf[MAXBUF];
	for (i = 1; i < argc; i++) {
		ret = stat(argv[i],&st);
		if (ret < 0) {
			snprintf(pf,MAXBUF,"Stat %s", argv[i]);
			perror(pf);
			continue;
		}
		buf = (char*)malloc(st.st_size);
		if (buf == NULL) {
			snprintf(pf,MAXBUF,"Malloc %s %ld",argv[i],st.st_size);
			perror(pf);
			continue;
		}
		fd = open(argv[i],O_RDONLY);
		if (fd < 0) {
			snprintf(pf,MAXBUF,"Open %s",argv[i]);
			perror(pf);
			continue;
		}
		rd = read(fd,buf,st.st_size);
		if (rd < 0) {
			snprintf(pf,MAXBUF,"Read %s",argv[i]);
			perror(pf);
			continue;
		}
		wr = write(STDOUT_FILENO,buf,st.st_size);
		if (wr < 0) {
			snprintf(pf,MAXBUF,"Write %s",argv[i]);
			perror(pf);
			continue;
		}
		free(buf);
	}
	return 0;
}
