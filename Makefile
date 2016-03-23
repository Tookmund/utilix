 # Makefile for utilix
 # Copyright 2016 Jacob Adams <tookmund@gmail.com>
 #
 # Permission is hereby granted, free of charge, to any person obtaining a
 # copy of this software and associated documentation files (the "Software"),
 # to deal in the Software without restriction, including without limitation
 # the rights to use, copy, modify, merge, publish, distribute, sublicense,
 # and/or sell copies of the Software, and to permit persons to whom the
 # Software is furnished to do so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included in
 # all copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 # FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 # DEALINGS IN THE SOFTWARE.

CFLAGS += -Wall -Werror
BIN = ${DESTDIR}/usr/local/bin

MANSUFFIX = 1
MANDIR = ${DESTDIR}/usr/local/share/man/man${MANSUFFIX}


# Should be alphabetical
TGTS= \
cat \
dd \
env \
ls \
mkdir \
new \
unenv \
unpg

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

# Generate .gitignore
gitignore:
	> .gitignore
	for i in ${TGTS} ; \
	do \
		echo $${i} >> .gitignore ; \
	done
