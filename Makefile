CC = gcc
CFLAGS = -O2
LDFLAGS =
ROOTDIR = $(CURDIR)
INCLUDE = $(CURDIR)/include
OUT = toylang

export CC CFLAGS LDFLAGS INCLUDE ROOTDIR

all: main

main:
	$(MAKE) -C ./src
	cp ./src/main $(OUT)

clean:
	$(MAKE) -C ./src clean 
	rm -f $(OUT)
