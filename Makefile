CC = gcc
AR = ar
CFLAGS = -O2 -Wall -MMD -MP
LDFLAGS =
ROOTDIR = $(CURDIR)
INCLUDE = $(CURDIR)/include
EXECUTABLE = toylang
ARCHIVE_NAME = archive.a

export CC AR CFLAGS LDFLAGS INCLUDE ROOTDIR ARCHIVE_NAME EXECUTABLE

all: main

main:
	$(MAKE) -C ./src

clean:
	$(MAKE) -C ./src clean 
	rm -f $(EXECUTABLE)
