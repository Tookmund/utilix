/*
 * Copyright (c) 2015 Jacob Adams
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copyof this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXBUF 1000
int main (int argc, char** argv) {
	int i;
	struct stat statbuf;
	struct stat *st = &statbuf;
	char* buf;
	int ret;
	int fd;
	int rd;
	int wr;
	char pf[MAXBUF];
	for (i = 1; i < argc; i++) {
		ret = stat(argv[i],st);
		if (ret < 0) {
			snprintf(pf,MAXBUF,"Stat %s", argv[i]);
			perror(pf);
			continue;
		}
		buf = (char*)malloc(st->st_size);
		if (buf == NULL) {
			snprintf(pf,MAXBUF,"Malloc %s %ld",argv[i],st->st_size);
			perror(pf);
			continue;
		}
		fd = open(argv[i],O_RDONLY);
		if (fd < 0) {
			snprintf(pf,MAXBUF,"Open %s",argv[i]);
			perror(pf);
			continue;
		}
		rd = read(fd,buf,st->st_size);
		if (rd < 0) {
			snprintf(pf,MAXBUF,"Read %s",argv[i]);
			perror(pf);
			continue;
		}
		wr = write(STDOUT_FILENO,buf,st->st_size);
		if (wr < 0) {
			snprintf(pf,MAXBUF,"Write %s",argv[i]);
			perror(pf);
			continue;
		}
	}
	return 0;
}
