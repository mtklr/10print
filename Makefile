# 10c Makefile

PROG = 10c

OS = $(shell uname -s)

ifeq ($(OS),Darwin)
CFLAGS += -D_XOPEN_SOURCE_EXTENDED -Os -Wall -Wextra #-O0 -g -Wall
LDLIBS = -lncurses
endif

ifeq ($(OS),Linux)
CFLAGS += -Os -Wall -Wextra #-O0 -g -Wall
LDLIBS = -lncursesw
endif

all: $(PROG)

$(PROG): $(PROG).o

clean:
	$(RM) $(PROG)
	$(RM) *.o

.PHONY: all clean
