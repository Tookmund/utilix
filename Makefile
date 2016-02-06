 # Makefile for utilix
 # Copyright (C) 2016 Jacob Adams <tookmund@gmail.com>
 #
 # This program is free software; you can redistribute it and/or
 # modify it under the terms of version 2 of the GNU General Public License
 # as published by the Free Software Foundation.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.

CFLAGS += -O2 -Wall -Werror
BIN = ${DESTDIR}/usr/local/bin

MANDIR = ${DESTDIR}/usr/local/share/man/man1
MANSUFFIX = 1

# Should be alphabetical
TGTS= \
cat \
ls

all: ${TGTS}

clean:
	rm ${TGTS}

install: ${TGTS}
	mkdir -p ${BIN}
	for i in ${TGTS} ; \
	do \
		cp $${i} ${BIN} ; \
	done

uninstall: ${TGTS}
	for i in ${TGTS} ; \
	do \
		rm ${BIN}/$${i} ; \
	done

# Borrowed from 9wm
# https://github.com/nealey/9wm
install.man:
	mkdir -p $(MANDIR)
	for i in ${TGTS} ; \
	do \
		cp $${i}.man $(MANDIR)/$${i}.$(MANSUFFIX) ; \
	done

uninstall.man:
	for i in ${TGTS} ; \
	do \
		rm ${MANDIR}/$${i}.${MANSUFFIX} ; \
	done
