EXE = SecureTcp-Np
LLIBS_LNX = -Wl,-R./libs/ -lmicrohttpd -lssh2
#LLIBS_LNX = -lssh2 -lgcrypt -lz -lgpg-error
LLIBS_WIN = -L. -lmicrohttpd -lssh2
#LLIBS_WIN = -lcurl -DCURL_STATICLIB -lbrotlidec-static -lbrotlicommon-static -lidn2 -lpsl -lunistring -lnghttp2 -lzstd -lwldap32 -lssl -lcrypt32 -liconv
#LLIBS_WIN += -lssh2 -lcrypto -lz -lws2_32 -lwsock32
LLIBS_OSX = -lmicrohttpd -lssh2
ILIBSINC_OSX = -I/usr/local/include
LLIBDIR_OSX = -L /usr/local/opt/libmicrohttpd/lib -L /usr/local/opt/libssh2/lib

OS_NAME=
OS_VER=
OS_DETAILS=Window
TARGET=win

ifeq ($(shell lsb_release -si),Ubuntu)
OS_NAME=$(shell lsb_release -si)
OS_VER=$(shell lsb_release -sr)
OS_DETAILS=$(OS_NAME)_$(OS_VER)
TARGET=lnx
else ifeq ($(shell uname),Darwin)
OS_NAME=$(shell sw_vers -productName)
OS_VER=$(shell sw_vers -productVersion)
OS_DETAILS=$(OS_NAME)_$(OS_VER)
TARGET=osx
endif

all:	$(TARGET)

lnx:	clean_exeb $(EXE)_x64_lnx clean_obj copy clean_exea copy_libs_lnx

win:	clean_exeb $(EXE)_x64_win clean_obj copy clean_exea copy_libs_win

osx:	clean_exeb $(EXE)_x64_osx clean_obj copy clean_exea dylibbundler_osx

$(EXE)_x64_lnx: ezini_x64_lnx.o os_x64_lnx.o opener_x64_lnx.o $(EXE)_x64_lnx.o
	gcc -m64 -no-pie -s ezini_x64.o os_x64.o opener_x64.o $(EXE)_x64.o $(LLIBS_LNX) -o $(EXE)_x64
	
$(EXE)_x64_lnx.o:
	gcc -c -m64 -no-pie -s $(EXE).c $(LLIBS_LNX) -o $(EXE)_x64.o
	
ezini_x64_lnx.o:
	gcc -c -m64 -no-pie -s ezini.c $(LLIBS_LNX) -o ezini_x64.o
	
os_x64_lnx.o:
	gcc -c -m64 -no-pie -s os.c $(LLIBS_LNX) -o os_x64.o
	
opener_x64_lnx.o:
	gcc -c -m64 -no-pie -s opener.c $(LLIBS_LNX) -o opener_x64.o

$(EXE)_x64_win:	favicon_win.o ezini_x64_win.o os_x64_win.o opener_x64_win.o $(EXE)_x64_win.o
	gcc -m64 -no-pie -s favicon.o ezini_x64.exe.o os_x64.exe.o opener_x64.exe.o $(EXE)_x64.exe.o $(LLIBS_WIN) -o $(EXE)_x64.exe
	
$(EXE)_x64_win.o:
	gcc -c -m64 -no-pie -s $(EXE).c $(LLIBS_WIN) -o $(EXE)_x64.exe.o

ezini_x64_win.o:
	gcc -c -m64 -no-pie -s ezini.c $(LLIBS_WIN) -o ezini_x64.exe.o
	
os_x64_win.o:
	gcc -c -m64 -no-pie -s os.c $(LLIBS_WIN) -o os_x64.exe.o
	
opener_x64_win.o:
	gcc -c -m64 -no-pie -s opener.c $(LLIBS_WIN) -o opener_x64.exe.o

favicon_win.o:
	windres -i favicon.rc -o favicon.o
	
$(EXE)_x64_osx: ezini_x64_osx.o os_x64_osx.o opener_x64_osx.o $(EXE)_x64_osx.o
	gcc -Bstatic -m64 -no-pie ezini_x64.o os_x64.o opener_x64.o $(EXE)_x64.o $(LLIBS_OSX) -o $(EXE)_x64 $(ILIBSINC_OSX) $(LLIBDIR_OSX)
	
$(EXE)_x64_osx.o:
	gcc -c -Bstatic -m64 -no-pie $(EXE).c $(LLIBS_OSX) -o $(EXE)_x64.o $(ILIBSINC_OSX) $(LLIBDIR_OSX)
	
ezini_x64_osx.o:
	gcc -c -Bstatic -m64 -no-pie ezini.c $(LLIBS_OSX) -o ezini_x64.o $(ILIBSINC_OSX) $(LLIBDIR_OSX)
	
os_x64_osx.o:
	gcc -c -Bstatic -m64 -no-pie os.c $(LLIBS_OSX) -o os_x64.o $(ILIBSINC_OSX) $(LLIBDIR_OSX)
	
opener_x64_osx.o:
	gcc -c -Bstatic -m64 -no-pie opener.c $(LLIBS_OSX) -o opener_x64.o $(ILIBSINC_OSX) $(LLIBDIR_OSX)
	
clean_obj:
	rm -rf *.o
	
clean_exeb:
	rm -rf *x64*

clean_exea:
	rm -rf *x64*

copy:
	mkdir -p $(OS_DETAILS)
	rm -rf $(OS_DETAILS)/*
	cp -rf *x64* $(OS_DETAILS)

copy_libs_lnx:
	mkdir -p $(OS_DETAILS)/libs
	ldd $(OS_DETAILS)/$(EXE)_x64 | grep "=> /" | awk '{print $$3}' | xargs -I '{}' cp -v '{}' $(OS_DETAILS)/libs/
		
copy_libs_win:
	ldd $(OS_DETAILS)/$(EXE)_x64.exe | grep "=> /mingw64" | awk '{print $$3}' | xargs -I '{}' cp -v '{}' $(OS_DETAILS)/

dylibbundler_osx:
	dylibbundler -od -b -x ./$(OS_DETAILS)/$(EXE)_x64 -d ./$(OS_DETAILS)/libs/ -p @executable_path/libs/
