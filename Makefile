CFLAGS ?= -g -Wall -Wextra

OBJS = sampler.o
HEADERS = sampler.h

PROGRAMS = test_cyc test_sub test_bubble

SAMPLEROBJS := $(addprefix libsampler/,$(OBJS))
PROGRAMEXES := $(addprefix programs/,$(PROGRAMS))
PROGRAMOBJS := $(addsuffix .o,$(PROGRAMEXES))
HEADERFILES := $(addprefix libsampler/,$(HEADERS))

all: libsampler/libsampler.a progs

progs: $(PROGRAMEXES)

libsampler/libsampler.a: $(SAMPLEROBJS)
	$(AR) rc $@ $^

%.o: %.c $(HEADERFILES)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROGRAMEXES): LDLIBS += -Llibsampler/ -lsampler
$(PROGRAMOBJS): CFLAGS += -Ilibsampler/

programs/%: programs/%.o libsampler/libsampler.a
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) libsampler/libsampler.a $(SAMPLEROBJS) $(PROGRAMEXES) $(PROGRAMOBJS)

.PHONY: all progs clean
