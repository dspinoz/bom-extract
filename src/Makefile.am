SUBDIRS = common

bin_PROGRAMS = hello pdf2png

hello_SOURCES = main.cpp
hello_CXXFLAGS =  -I../external/dist/include -Icommon 
hello_LDFLAGS = -L../external/dist/lib -L/usr/lib -static-libgcc -static-libstdc++
hello_LDADD = common/libcommon.a \
	../external/dist/lib/libtesseract.a \
	../external/dist/lib/liblept.a \
	../external/dist/lib/libgif.a \
	../external/dist/lib/libjpeg.a \
	../external/dist/lib/libpng.a \
	../external/dist/lib/libtiff.a \
	../external/dist/lib/libtiff.a \
	../external/dist/lib/libjbig.a \
	../external/dist/lib/libwebp.a \
	../external/dist/lib/libz.a -lws2_32

pdf2png_SOURCES = pdf2png.c
pdf2png_CFLAGS =  -I../external/dist/include
pdf2png_LDFLAGS = -L../external/dist/lib -L/usr/lib
pdf2png_LDADD = ../external/dist/lib/libmupdf.a \
	../external/dist/lib/libmupdfthird.a 
  
check_SCRIPTS = greptest.sh
TESTS = $(check_SCRIPTS)

greptest.sh:
	echo './hello | grep -i "hello"' > greptest.sh
	chmod +x greptest.sh

CLEANFILES = greptest.sh
