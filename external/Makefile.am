
TOP=$(shell pwd)/dist

bin_SCRIPTS = $(TOP)/bin/tesseract.exe \
	$(TOP)/lib/libpthread.a \
	$(TOP)/lib/libz.a \
	$(TOP)/lib/liblzma.a \
	$(TOP)/lib/libpng.a \
	$(TOP)/lib/libgif.a \
	$(TOP)/lib/libjpeg.a \
	$(TOP)/lib/libjbig.a \
	$(TOP)/lib/libtiff.a \
	$(TOP)/lib/libwebp.a \
	$(TOP)/lib/liblept.a \
	$(TOP)/lib/libtesseract.a

sources.txt:
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
	cd $($@_DIR) && cp -v pthread.h semaphore.h sched.h $(TOP)/include
	cd $($@_DIR) && cp -v libpthreadGC2.a $(TOP)/lib/libpthread.a
	
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

$(TOP)/lib/libpng.a: $(TOP)/lib/libz.a libpng-1.5.26.tar.gz
	$(eval $@_TAR := $(filter %.tar.gz, $^))
	$(eval $@_DIR := $(basename $(basename $(notdir $($@_TAR)))) )
	rm -rf $($@_DIR)
	tar xf $($@_TAR)
	cd $($@_DIR) && ./configure --prefix=$(TOP) CFLAGS=-I$(TOP)/include LDFLAGS=-L$(TOP)/lib
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
	
$(TOP)/lib/libjpeg.a: jpeg-9b.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && ./configure --prefix=$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install
	
$(TOP)/lib/libjbig.a: jbigkit-2.1.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && make lib
	cd $($@_DIR) && cp -v libjbig/libjbig.a $(TOP)/lib/libjbig.a
	cd $($@_DIR) && cp -v libjbig/jbig.h $(TOP)/include/jbig.h
	
# libz libjpeg libjbig
$(TOP)/lib/libtiff.a: tiff-3.9.5.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && ./autogen.sh
	cd $($@_DIR) && ./configure --prefix=$(TOP) CFLAGS=-I$(TOP) LDFLAGS=-L$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install
	
# libpng libjpeg libtiff
$(TOP)/lib/libwebp.a: libwebp-0.5.0.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && ./autogen.sh
	cd $($@_DIR) && ./configure --prefix=$(TOP) CFLAGS=-I$(TOP) LDFLAGS=-L$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install
	
$(TOP)/lib/liblept.a: leptonica-1.73.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && ./autobuild
	cd $($@_DIR) && ./configure --prefix=$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install

tesseract-3.04.01.tar.gz: download.sh
	./download.sh
  
$(TOP)/lib/libtesseract.a: $(TOP)/lib/libtiff.a $(TOP)/lib/liblept.a tesseract-3.04.01.tar.gz
	$(eval $@_TAR := $(filter %.tar.gz, $^))
	$(eval $@_DIR := $(basename $(basename $(notdir $($@_TAR)))) )
	rm -rf $($@_DIR)
	tar xf $($@_TAR)
	cd $($@_DIR) && autogen.sh
	cd $($@_DIR) && ./configure --prefix=$(TOP) CPPFLAGS=-I$(TOP)/include LDFLAGS=-L$(TOP)/lib
	cd $($@_DIR) && make
	cd $($@_DIR) && make install
  
  