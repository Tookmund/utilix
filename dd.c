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
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MB is 1000 KD is 1000 B
#define MB (1000*1000*1000)
#define ERRSIZE 100

int main (int argc, char* argv[]) {
	if (argc < 3 || argc > 4) {
		printf("%s [input] [output] [optional-blocksize-in-MB]",argv[0]);
	}
	int ifd;
	int ofd;
	char* buf;
	// Check stdin and stdout (indicated by - )
	if (!strcmp(argv[1],"-")) {
		ifd = 0;
	}
	if (!strcmp(argv[2],"-")) {
		ofd = 1;
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
		bs = MB;
		buf = (char*)malloc(bs);
		if (buf == NULL) {
			perror("Malloc");
			return 1;
		}
		int rd;
		int wr;
		while ( !(rd < 0 && wr < 0) ) {
			rd = read(ifd,buf,bs);
			wr = write(ofd,buf,bs);
		}
	}
	free(buf);
	return 0;
}
