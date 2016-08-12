/* ish.h -- Helper functions for ish
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
void prompt()
{
	char* user = getenv("USER");
	char* pwd = getenv("PWD");
	printf("%s@%s[$] ", user, pwd);
}

char** getargv(char* s, char* delim)
{
	char* arg = strtok(s,delim);
	if (arg == NULL) return NULL;
	size_t argc = sizeof(char*)*2;
	int i = 1;
	char** argv = malloc(argc);
	if (argv == NULL)
	{
		perror("ish argv malloc");
		return NULL;
	}
	argv[0] = arg;
	while (arg != NULL)
	{
		arg = strtok(NULL,delim);
		if (arg == NULL) continue;
		argc += sizeof(char*);
		argv = realloc(argv,argc);
		if (argv == NULL)
		{
			perror("ish argv realloc");
			free(argv);
			return NULL;
		}
		argv[i] = arg;
		i++;
	}
	argv[i] = NULL;
	return argv;
}

int checkkeywords (char** argv)
{
	int ret = 1;
	if (strcmp(argv[0],"exit") == 0) exit(0);
	else if (strcmp(argv[0],"cd") == 0)
	{
		if (argv[1] != NULL) chdir(argv[1]);
		else chdir(getenv("HOME"));
		setenv("PWD",getcwd(NULL,0),1);
	}
	else ret = 0;
	return ret;
}

int run (char* s,int in,int out)
{
	char** argv = getargv(s," ");
	if (argv == NULL) return -1;
	if (checkkeywords(argv)) return 0;
	int pid = fork();
	switch (pid)
	{
		case 0:
			if (in != 0) dup2(in,0);
			if (out != 1) dup2(out,1);
			execvp(argv[0],argv);
			// Only returns if something went wrong
			perror("ish execvp");
			break;
		case -1:
			perror("ish fork");
		default:
			free(argv);
			if (in != 0) close(in);
			if (out != 1) close(out);
			return pid;
	}
	return 0;
}
