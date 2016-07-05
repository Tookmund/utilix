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

// MB is 1000 KD is 1000 B
#define MB (1000*1000*1000)
#define ERRSIZE 100

int main (int argc, char* argv[]) {
	if (argc < 3 || argc > 4) {
		printf("%s [input] [output] [optional-blocksize-in-MB]",argv[0]);
	}
	FILE* iff;
	FILE* off;
	void* buf;
	// Check stdin and stdout (indicated by - )
	if (strcmp(argv[1],"-") == 0) {
		iff = stdin;
	}
	else
	{
		iff = fopen(argv[1], "r");
		if (iff == NULL)
		{
			perror("dd iff open");
			return 1;
		}
	}
	if (strcmp(argv[2],"-") == 0) {
		off = stdout;
	}
	else
	{
		off = fopen(argv[2],"w");
		if (off == NULL)
		{
			perror("dd off open");
			return 1;
		}
	}
	int bs;
	if (argc == 4) {
		bs = strtol(argv[3],NULL,10)*MB;
		if (bs <= 0) bs = MB;
		buf = malloc(bs);
		if (buf == NULL) {
			perror(argv[3]);
			return 1;
		}
	}
	else {
		bs = 1000;
		buf = malloc(bs);
		if (buf == NULL) {
			perror("Malloc");
			return 1;
		}
	}
	int rd = 1;
	int wr = 1;
	while (rd > 0 && wr >= 0)
	{
		rd = fread(buf,bs,1,iff);
		if (rd < 0)
		{
			perror("dd iff read");
			return 1;
		}
		wr = fwrite(buf,bs,1,off);
		if (wr < 0)
		{
			perror("dd off write");
			return 1;
		}
		memset(buf,0,bs);
	}
	free(buf);
	return 0;
}
