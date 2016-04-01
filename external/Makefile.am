
TOP=$(shell pwd)/dist

bin_SCRIPTS = $(TOP)/lib/liblzma.a

$(TOP): $(TOP)/lib
	mkdir $(TOP)

$(TOP)/lib:
	mkdir $(TOP)/lib

$(TOP)/lib/liblzma.a: xz-5.2.2.tar.gz
	$(eval $@_DIR := $(basename $(basename $(notdir $<))) )
	cd $($@_DIR) && ./configure --prefix=$(TOP)
	cd $($@_DIR) && make
	cd $($@_DIR) && make install

