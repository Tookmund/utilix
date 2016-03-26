/*
 * dd -- Data Dump
 *
 * Copyright 2016 Jacob Adams <tookmund@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
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

// dd [input] [output] [blocksize]

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "perm.h"

// MB is 1000 KD is 1000 B
#define MB (1000*1000*1000)
#define ERRSIZE 100

int main (int argc, char* argv[]) {
	if (argc < 3 || argc > 4) {
		printf("%s [input] [output] [optional-blocksize-in-MB]",argv[0]);
	}
	int ifd;
	int ofd;
	mode_t mode = FILEMODE;
	char* buf;
	// Check stdin and stdout (indicated by - )
	if (strcmp(argv[1],"-") == 0) {
		ifd = 0;
	}
	else
	{
		ifd = open(argv[1], O_RDONLY | O_CREAT,mode);
		if (ifd  < 0)
		{
			perror("dd ifd open");
			return 1;
		}
		// Get mode
		struct stat st;
		int e = fstat(ifd,&st);
		if (e < 0) perror("dd ifd fstat");
		else mode = st.st_mode;
	}
	if (strcmp(argv[2],"-") == 0) {
		ofd = 1;
	}
	else
	{
		ofd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,mode);
		if (ofd < 0)
		{
			perror("dd ofd open");
			return 1;
		}
	}
	int bs;
	if (argc == 4) {
		bs = strtol(argv[3],NULL,10)*MB;
		if (bs <= 0) bs = MB;
		buf = (char*)malloc(bs);
		if (buf == NULL) {
			perror(argv[3]);
			return 1;
		}
	}
	else {
		bs = 1000;
		buf = (char*)malloc(bs);
		if (buf == NULL) {
			perror("Malloc");
			return 1;
		}
	}
	int rd;
	int wr;
	// Non-blocking reads and writes
	int fc = fcntl(ifd, F_SETFD, O_NONBLOCK);
	if (fc < 0)
	{
		perror("dd ifd fcntl");
		return 1;
	}
	fc = fcntl(ofd, F_SETFD, O_NONBLOCK);
	if (fc < 0)
	{
		perror("dd ofd fcntl");
		return 1;
	}
	while (rd > 0 && wr >= 0)
	{
		rd = read(ifd,buf,bs);
		if (rd < 0)
		{
			perror("dd ifd read");
			return 1;
		}
		wr = write(ofd,buf,bs);
		if (wr < 0)
		{
			perror("dd ofd write");
			return 1;
		}
		memset(buf,0,bs);
	}
	free(buf);
	return 0;
}
