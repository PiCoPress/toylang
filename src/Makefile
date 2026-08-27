SRCS = pi.c main.c
OBJS = $(SRCS:.c=.o)
SUBDIRS =
TARGET = main

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -I$(INCLUDE) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o $@ $<

clean:
	for dir in $(SUBDIRS); \
		do $(MAKE) -C $$dir clean; \
	done

	rm -f $(OBJS) main.o
