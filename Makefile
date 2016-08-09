CC := clang

SRCDIR := src
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(addsuffix .o,$(basename $(notdir $(SOURCES))))

GMPDIR := vendor/gmp-6.1.1
GMPBUILDDIR := gmp-6.1.1
GMPLIB := $(GMPBUILDDIR)/libgmp.la

CFLAGS ?= -O3 -Wall -Wextra -Werror -std=c++11 -pedantic -I$(GMPBUILDDIR) -DNDEBUG
DFLAGS ?= -Wall -Wextra -Werror -std=c++11 -pedantic -I$(GMPBUILDDIR) -g
LFLAGS ?= -L$(GMPDIR) -lstdc++ -lgmp

TARGET ?= ploy

.PHONY: all dbg clean clean-all

all: $(TARGET)

dbg:
	$(eval CFLAGS := $(DFLAGS))
	$(eval export CFLAGS)
	$(MAKE)

$(TARGET): $(GMPLIB) $(OBJECTS)
	$(CC) $(LFLAGS) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(GMPLIB):
	cp -r $(GMPDIR) $(GMPBUILDDIR)
	cd $(GMPBUILDDIR) && ./configure && make && make check

%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: $(SRCDIR)/*/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJECTS) $(TARGET)

clean-all:
	rm -rf $(OBJECTS) $(TARGET) $(GMPBUILDDIR)
