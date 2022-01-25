CFLAGS ?= -g -Wall -Wextra

OBJS = sampler.o
HEADERS = sampler.h

PROGRAMS = test_cyc test_sub test_bubble test_bubble2 empty \
    inttrapez-1full inttrapez-2full inttrapez-1part inttrapez-2part

SAMPLEROBJS := $(addprefix libsampler/,$(OBJS))
PROGRAMEXES := $(addprefix programs/,$(PROGRAMS))
PROGRAMOBJS := $(addsuffix .o,$(PROGRAMEXES))
HEADERFILES := $(addprefix libsampler/,$(HEADERS))

all: libsampler/libsampler.a progs tools/repeat

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

tools/repeat: tools/repeat.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) libsampler/libsampler.a $(SAMPLEROBJS) $(PROGRAMEXES) $(PROGRAMOBJS) tools/repeat

.PHONY: all progs clean
