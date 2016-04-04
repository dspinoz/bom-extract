
TOP=$(shell pwd)/dist

bin_SCRIPTS = $(TOP)/bin/tesseract.exe $(TOP)/lib/libpthread.a $(TOP)/lib/liblzma.a

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
	
$(TOP)/lib/liblzma.a: xz-5.2.2.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	rm -rf $($@_DIR)
	tar xf $<
	cd $($@_DIR) && ./configure --prefix=$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install
