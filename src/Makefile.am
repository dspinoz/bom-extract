SUBDIRS = common

bin_PROGRAMS = hello
hello_SOURCES = main.cpp
hello_CXXFLAGS = -D__BLOB_T_DEFINED -I../external/dist/include -Icommon 
hello_LDFLAGS = -L../external/dist/lib -L/usr/lib
hello_LDADD = common/libcommon.a \
	../external/dist/lib/libtesseract.a \
	../external/dist/lib/liblept.a \
	../external/dist/lib/libgif.a \
	../external/dist/lib/libjpeg.a \
	../external/dist/lib/libpng.a \
	../external/dist/lib/libtiff.a \
	../external/dist/lib/libtiffxx.a \
	../external/dist/lib/libjbig.a \
	../external/dist/lib/libwebp.a \
	-lz -lws2_32

check_SCRIPTS = greptest.sh
TESTS = $(check_SCRIPTS)

greptest.sh:
	echo './hello | grep -i "hello"' > greptest.sh
	chmod +x greptest.sh

CLEANFILES = greptest.sh
