SRCS = const_data.c main.c parser.c tokenizer.c stringtools.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
SUBDIRS = tokenizers
SUBDIR_ARC = $(addsuffix /$(ARCHIVE_NAME),$(SUBDIRS))

.PHONY: $(SUBDIRS) all clean

all: $(SUBDIRS) ../$(EXECUTABLE)

../$(EXECUTABLE): $(SUBDIR_ARC) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INCLUDE) -o ../$(EXECUTABLE) $(OBJS) $(SUBDIR_ARC)

$(SUBDIRS):
	$(MAKE) -C $@

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o $@ $<

const_data.o: ../include/ast/tokens.h
	../scripts/gen_const_data.sh $< const_data.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o $@ const_data.c

clean:
	@for dir in $(SUBDIRS); \
		do $(MAKE) -C $$dir clean; \
	done

	rm -f $(OBJS) $(DEPS)

-include $(OBJS:.o=.d)
