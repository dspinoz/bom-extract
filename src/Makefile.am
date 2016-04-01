SUBDIRS = common

bin_PROGRAMS = hello
hello_SOURCES = main.cpp
hello_CXXFLAGS = -D__BLOB_T_DEFINED -I../external/dist/include -Icommon 
hello_LDFLAGS = -L../external/dist/lib 
hello_LDADD = common/libcommon.a -llept -ltesseract

check_SCRIPTS = greptest.sh
TESTS = $(check_SCRIPTS)

greptest.sh:
	echo './hello | grep -i "hello"' > greptest.sh
	chmod +x greptest.sh

CLEANFILES = greptest.sh
