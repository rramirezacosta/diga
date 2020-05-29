APP_NAME = diga
SPEC_FILE = diga.spec
VERSION = 1.0.0
TAR_DIR = /tmp/$(APP_NAME)-$(VERSION)
RPM_BUILDDIR = ~/rpmbuild

CPP=g++
WCPP=x86_64-w64-mingw32-g++
W32CPP=i686-w64-mingw32-g++

LFLAGS= -lspeechd
WLFLAGS= -static-libgcc -static-libstdc++ -lsapi -lole32
SRC=./src/main.cpp
TAR_DIR = /tmp/$(APP_NAME)-$(VERSION)


all:
	$(info )
	$(info options:)
	$(info )
	$(info *     make binaries        -builds binaries (linux))
	$(info *     make wbinaries       -builds binaries (Windows 10))
	$(info *     make local-install   -install diga for the current user on ~/.local/bin/ (linux))
	$(info *     make install         -install diga for all users (linux, root required))
	$(info *     make rpm             -creates a RPM package (linux))
	$(info *     make win-installer   -creates a NSIS windows installer (Windows 10))
	$(info )
	$(info )

binaries:
	mkdir -p ./bin
	$(CPP) $(SRC) $(LFLAGS) -o ./bin/say
	$(CPP) $(SRC) $(LFLAGS) -DLANG=es -o ./bin/diga

wbinaries:
	mkdir -p ./bin 
	$(WCPP) $(SRC) $(WLFLAGS) -o ./bin/say


local-install:
	cp ./bin/say ~/.local/bin/
	cp ./bin/diga ~/.local/bin/

install:
	cp ./bin/say /usr/bin/
	cp ./bin/diga /usr/bin/
	chown root:root /usr/bin/diga
	chown root:root /usr/bin/say
	chmod 751 /usr/bin/diga
	chmod 751 /usr/bin/say
	
rpm: binaries
	if [ -d $(TAR_DIR) ]; then rm -rf $(TAR_DIR); fi
	mkdir -p $(TAR_DIR)/usr/bin
	cp ./bin/say $(TAR_DIR)/usr/bin/
	cp ./bin/diga $(TAR_DIR)/usr/bin/
	mkdir -p $(RPM_BUILDDIR)/{BUILD,RPMS,SOURCES,SPECS,SRPMS};
	if [ -f $(RPM_BUILDDIR)/SOURCES/$(APP_NAME)-$(VERSION).tar.gz ]; then rm $(RPM_BUILDDIR)/SOURCES/$(APP_NAME)-$(VERSION).tar.gz; fi
	cd /tmp; tar -zcvf $(APP_NAME)-$(VERSION).tar.gz $(APP_NAME)-$(VERSION); mv $(APP_NAME)-$(VERSION).tar.gz $(RPM_BUILDDIR)/SOURCES
	rpmbuild -bb $(SPEC_FILE)

clean:
	rm -rf ./bin
