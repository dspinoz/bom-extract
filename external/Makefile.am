
TOP=$(shell pwd)/dist

bin_SCRIPTS = $(TOP)/lib/libpthread.a \
	$(TOP)/lib/libz.a \
	$(TOP)/lib/liblzma.a \
	$(TOP)/lib/libpng.a \
	$(TOP)/lib/libgif.a \
	$(TOP)/lib/libjpeg.a \
	$(TOP)/lib/libjbig.a \
	$(TOP)/lib/libtiff.a \
	$(TOP)/lib/libwebp.a \
	$(TOP)/lib/liblept.a \
	$(TOP)/lib/libtesseract.a \
	$(TOP)/bin/cmake.exe \
	$(TOP)/lib/libfreetype.a \
	$(TOP)/lib/libpodofo.a

sources.txt:
	./download.sh

.PHONY: $(TOP) $(TOP)/bin $(TOP)/include $(TOP)/lib
  
$(TOP): all
	mkdir -p $(TOP)/bin $(TOP)/include $(TOP)/lib
  
# Disabled
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
	
$(TOP)/lib/liblept.a: $(TOP)/lib/libtiff.a $(TOP)/lib/libjpeg.a $(TOP)/lib/libpng.a  $(TOP)/lib/libtiff.a $(TOP)/lib/libz.a $(TOP)/lib/libwebp.a $(TOP)/lib/libgif.a leptonica-1.73.tar.gz
	$(eval $@_TAR := $(filter %.tar.gz, $^))
	$(eval $@_DIR := $(basename $(basename $(notdir $($@_TAR)))) )
	rm -rf $($@_DIR)
	tar xf $($@_TAR)
	cd $($@_DIR) && ./autobuild
	cd $($@_DIR) && ./configure --prefix=$(TOP) CPPFLAGS=-I$(TOP)/include LDFLAGS=-L$(TOP)/lib
	cd $($@_DIR) && make
	cd $($@_DIR) && make install

tesseract-3.04.01.tar.gz: download.sh
	./download.sh
  
$(TOP)/lib/libtesseract.a: $(TOP)/lib/liblept.a tesseract-3.04.01.tar.gz
	$(eval $@_TAR := $(filter %.tar.gz, $^))
	$(eval $@_DIR := $(basename $(basename $(notdir $($@_TAR)))) )
	rm -rf $($@_DIR)
	tar xf $($@_TAR)
	cd $($@_DIR) && patch -p1 < ../tesseract.patch
	cd $($@_DIR) && autogen.sh
	cd $($@_DIR) && ./configure --prefix=$(TOP) LIBLEPT_HEADERSDIR=$(TOP)/include CPPFLAGS=-I$(TOP)/include LDFLAGS=-L$(TOP)/lib
	cd $($@_DIR) && make
	cd $($@_DIR) && make install
  
$(TOP)/bin/cmake.exe: cmake-2.8.3-win32-x86.zip
	$(eval $@_ZIP := $(filter %.zip, $^))
	$(eval $@_DIR := $(basename $(notdir $($@_ZIP))) )
	rm -rf $($@_DIR)
	unzip -q $($@_ZIP)
	cd $($@_DIR) && cp bin/* $(TOP)/bin/
	cd $($@_DIR) && cp -r share/cmake-2.8 $(TOP)/share/

$(TOP)/lib/libfreetype.a: $(TOP)/lib/libpng.a $(TOP)/lib/libz.a freetype-2.6.3.tar.gz
	$(eval $@_TAR := $(filter %.tar.gz, $^))
	$(eval $@_DIR := $(basename $(basename $(notdir $($@_TAR)))) )
	rm -rf $($@_DIR)
	tar xf $($@_TAR)
	cd $($@_DIR) && autogen.sh
	cd $($@_DIR) && ./configure --prefix=$(TOP) CPPFLAGS=-I$(TOP)/include LDFLAGS=-L$(TOP)/lib
	cd $($@_DIR) && make
	cd $($@_DIR) && make install
  
# use podofo-0.9.1 as libcrypt is not a mandatory dependency
# use cmake-2.8.3 as has "windres.exe -- W invalid option" error
$(TOP)/lib/libpodofo.a: $(TOP)/bin/cmake.exe $(TOP)/lib/libtiff.a $(TOP)/lib/libjpeg.a $(TOP)/lib/libpng.a  $(TOP)/lib/libfreetype.a $(TOP)/bin/cmake.exe podofo-0.9.1.tar.gz
	$(eval $@_TAR := $(filter %.tar.gz, $^))
	$(eval $@_DIR := $(basename $(basename $(notdir $($@_TAR)))) )
	rm -rf $($@_DIR)
	tar xf $($@_TAR)
	cd $($@_DIR) && mkdir build
	cd $($@_DIR) && cd build && cmake -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=$(TOP) -DCMAKE_INCLUDE_PATH=$(TOP)/include -DCMAKE_INCLUDE_PATH=$(TOP)/include/freetype2 -DCMAKE_LIBRARY_PATH=$(TOP)/lib -DPODOFO_BUILD_SHARED:BOOL=FALSE ..
	cd $($@_DIR) && cd build && make
	cd $($@_DIR) && cd build && make install


