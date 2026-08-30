SRCS = const_data.c main.c parser.c tokenizer.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
SUBDIRS =
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -I$(INCLUDE) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o $@ $<

clean:
	for dir in $(SUBDIRS); \
		do $(MAKE) -C $$dir clean; \
	done

	rm -f $(OBJS) $(DEPS) $(TARGET)

-include $(OBJS:.o=.d)
