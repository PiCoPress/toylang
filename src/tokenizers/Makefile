SRCS = words.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
SUBDIRS =
SUBDIR_ARC = $(addsuffix /$(ARCHIVE_NAME),$(SUBDIRS))

.PHONY: $(SUBDIRS) all clean

all: $(SUBDIRS) $(ARCHIVE_NAME)

$(ARCHIVE_NAME): $(SUBDIRS) $(OBJS)
	$(AR) rcs $(ARCHIVE_NAME) $(OBJS)

$(SUBDIRS):
	$(MAKE) -C $@

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o $@ $<

clean:
	@for dir in $(SUBDIRS); \
		do $(MAKE) -C $$dir clean; \
	done

	rm -f $(OBJS) $(DEPS) $(ARCHIVE_NAME)

-include $(OBJS:.o=.d)
