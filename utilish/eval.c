/* eval.c -- Evaluate a line of shell code
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

#include "ish.h"
#include <sys/wait.h>
void eval(char* s, int pipes)
{
        pid_t* pids = malloc(sizeof(pid_t*)*(pipes+1));
        if (!pipes) pids[0] = run(s,0,1);
        else
        {
                char** programs = getarray(s,"|");
                if (programs == NULL) return;
                int* oldpipes = NULL;
                int* newpipes = NULL;
                for (int i = 0; i <= pipes; i++)
                {
                        newpipes = malloc(sizeof(int)*2);
                        if (newpipes == NULL)
                        {
                                perror("ish malloc newpipes");
                                return;
                        }
                        int p = pipe(newpipes);
                        if (p < 0)
                        {
                                perror("ish pipe");
                                return;
                        }
                        if (programs[i+1] == NULL) newpipes[1] = 1;
                        if (oldpipes == NULL) pids[i] = run(programs[i],0,newpipes[1]);
                        else pids[i] = run(programs[i],oldpipes[0],newpipes[1]);
                        free(oldpipes);
                        oldpipes = newpipes;
                }
        }
        // Allow everything to finish up
        for (int i = 0; i <= pipes; i++)
        {
                waitpid(pids[i],NULL,0);
        }
}
