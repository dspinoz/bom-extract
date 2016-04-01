
TOP=$(shell pwd)/dist

bin_SCRIPTS = $(TOP)/bin/tesseract.exe 

$(TOP)/bin/tesseract.exe: tesseract-mingw-master.tar.gz
	tar xf $<
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	mv $($@_DIR) $(TOP)
	touch $(TOP)/bin/tesseract.exe
	
$(TOP)/lib/liblzma.a: xz-5.2.2.tar.gz
	tar xf $<
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	cd $($@_DIR) && ./configure --prefix=$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install
