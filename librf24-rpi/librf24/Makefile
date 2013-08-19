#############################################################################
#
# Makefile for librf24 on Raspberry Pi
#
# License: GPL (General Public License)
# Author:  gnulnulf <arco@appeltaart.mine.nu>
# Date:    2013/02/07 (version 1.0)
#
# Description:
# ------------
# use make all and mak install to install the library 
# You can change the install directory by editing the LIBDIR line
#
LIBDIR=/usr/local/lib
LIBNAME_BASE=librf24.so
LIBNAME=${LIBNAME_BASE}.1.0


# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

# make all
all: librf24

# Make the library
librf24: RF24.o gpio.o spi.o compatibility.o
	$(CXX) -shared -Wl,-soname,librf24.so.1 ${CCFLAGS}  -o ${LIBNAME} compatibility.o gpio.o spi.o RF24.o
	ln -sf ${LIBNAME} ${LIBNAME_BASE}


# Library parts
RF24.o: RF24.CXX
	$(CXX) -Wall -fPIC ${CCFLAGS} -c RF24.CXX

gpio.o: gpio.CXX
	$(CXX) -Wall -fPIC ${CCFLAGS} -c gpio.CXX

spi.o: spi.CXX
	$(CXX) -Wall -fPIC ${CCFLAGS} -c spi.CXX

compatibility.o: compatibility.c
	$(CXX) -Wall -fPIC  ${CCFLAGS} -c compatibility.c

# clear build files
clean:
	rm -rf *o ${LIBNAME}
	unlink ${LIBNAME_BASE}

# Install the library to LIBPATH
install: 
	cp librf24.so.1.0 ${LIBDIR}/${LIBNAME}
	ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/${LIBNAME_BASE}.1
	ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/${LIBNAME_BASE}
	ldconfig

