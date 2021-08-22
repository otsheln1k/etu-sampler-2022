CFLAGS ?= -g -Wall -Wextra

OBJS = sampler.o
HEADERS = sampler.h

PROGRAMS = test_cyc test_sub test_bubble test_bubble2 empty

SAMPLEROBJS := $(addprefix libsampler/,$(OBJS))
PROGRAMEXES := $(addprefix programs/,$(PROGRAMS))
PROGRAMOBJS := $(addsuffix .o,$(PROGRAMEXES))
HEADERFILES := $(addprefix libsampler/,$(HEADERS))

all: libsampler/libsampler.a progs

progs: $(PROGRAMEXES)

libsampler/libsampler.a: $(SAMPLEROBJS)
	$(AR) rc $@ $^

libsampler/%.o: libsampler/%.c $(HEADERFILES)
	$(CC) $(CFLAGS) -c -o $@ $<

programs/%.o: programs/%.c libsampler/sampler.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROGRAMEXES): LDLIBS += -Llibsampler/ -lsampler
$(PROGRAMOBJS): CFLAGS += -Ilibsampler/

programs/%: programs/%.o libsampler/libsampler.a
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) libsampler/libsampler.a $(SAMPLEROBJS) $(PROGRAMEXES) $(PROGRAMOBJS)

.PHONY: all progs clean
