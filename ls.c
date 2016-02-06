/*
 * ls -- List contents of a directory
 * Copyright (C) 2016 Jacob Adams <tookmund@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#define MAXBUF 1000

void lsdir(char* path) {
	char pf[MAXBUF];
	DIR* dir = opendir(path);
	if (dir == NULL) {
		snprintf(pf,MAXBUF,"Open %s",path);
		perror(pf);
		return;
	}
	struct dirent* ent = readdir(dir);
	while (ent != NULL) {
		printf("%s\n",ent->d_name);
		ent = readdir(dir);
	}
}

int main (int argc, char *argv[]) {
	if (argc == 1) {
		lsdir(".");
	}
	else {
		int i;
		for (i = 0; i < argc; i++) {
			lsdir(argv[i]);
		}
	}
}

