
TOP=$(shell pwd)/dist

bin_SCRIPTS = $(TOP)/bin/tesseract.exe \
	$(TOP)/lib/libpthread.a \
	$(TOP)/lib/libz.a \
	$(TOP)/lib/liblzma.a \
	$(TOP)/lib/libpng.a \
	$(TOP)/lib/libgif.a

tesseract-mingw-master.tar.gz: download.sh
	./download.sh

$(TOP)/bin/tesseract.exe: tesseract-mingw-master.tar.gz
	rm -rf tesseract-mingw-master $(TOP)
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	mv $($@_DIR) $(TOP)
	touch $(TOP)/bin/tesseract.exe
	
$(TOP)/lib/libpthread.a: pthreads-w32-2-8-0-release.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && patch -p1 < ../pthreads-w32.patch
	cd $($@_DIR) && CFLAGS="-DHAVE_STRUCT_TIMESPEC" CPPFLAGS="-DPTW32_STATIC_LIB" make clean GC-static
	cd $($@_DIR) && cp -iv pthread.h semaphore.h sched.h $(TOP)/include
	cd $($@_DIR) && cp -iv libpthreadGC2.a $(TOP)/lib/libpthread.a
	
$(TOP)/lib/libz.a: zlib-1.2.8.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && make -f win32/Makefile.gcc
	cd $($@_DIR) && DESTDIR=$(TOP) LIBRARY_PATH=/lib BINARY_PATH=/bin INCLUDE_PATH=/include make -f win32/Makefile.gcc install
	
$(TOP)/lib/liblzma.a: xz-5.2.2.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && ./configure --prefix=$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install

$(TOP)/lib/libpng.a: libpng-1.5.26.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && ./configure --prefix=$(TOP) CFLAGS=-I$(TOP) LDFLAGS=-L$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install

$(TOP)/lib/libgif.a: giflib-5.1.4.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && patch -p1 < ../giflib.patch
	cd $($@_DIR) && autoreconf --install --force
	cd $($@_DIR) && ./configure --prefix=$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install