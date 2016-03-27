/* stat -- Print one-line status of a file or directory
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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

void printstats(char* path,size_t s)
{
	struct stat st;
	// Remove last newline
	if (s > 1) path[s-1] = 0;
	int e = stat(path,&st);
	if (e < 0) perror(path);
	else printf("%o %lld %s\n",st.st_mode,st.st_size,path);
}
int main (int argc, char** argv)
{
	char* line = NULL;
	size_t n = 0;
	ssize_t e = 1;
	while (e != -1)
	{
		printstats(line,e);
		e = getline(&line,&n,stdin);
		if (e < 0) perror(argv[1]);
	}
	return 0;
}

