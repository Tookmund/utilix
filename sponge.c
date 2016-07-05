/* sponge -- Output all of stdin to stdout
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

// sponge [filename]

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "perm.h"

#define BUFSIZE 8192

int main (int argc, char** argv)
{
	if (argc < 2)
	{
		printf("%s [filename]\n",argv[0]);
		exit(1);
	}
	char buf[BUFSIZE];
	int fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC | O_NONBLOCK,FILEMODE);
	if (fd < 0)
	{
		perror("sponge: open file");
		exit(1);
	}
	int r = 1;
	int w = 0;
	while (r != 0)
	{
		memset(buf,0,BUFSIZE);		
		r = read(0,buf,BUFSIZE);
		if (r < 0 && (errno == EAGAIN || errno == EWOULDBLOCK) ) continue;
		if (r < 0)
		{
			perror("sponge read");
			exit(1);
		}
		else
		{
			w = write(fd,buf,r);
			if (w < 0)
			{
				perror("sponge write");
				exit(1);
			}
		}
	}
}
