MAKEFLAGS += -r

CXX := clang-3.8

SRCDIR := src
OBJDIR := obj
BUILDDIR := build

SOURCES := $(shell find $(SRCDIR) -name '*.cpp')

LIBRARY := $(SRCDIR)/library.ply
LIBRARY_SOURCE := $(LIBRARY:$(SRCDIR)/%.ply=$(BUILDDIR)/%.cpp)
LIBRARY_HEADER := $(LIBRARY_SOURCE:.cpp=.h)
LIBRARY_OBJECT := $(LIBRARY_SOURCE:$(BUILDDIR)/%.cpp=$(OBJDIR)/%.o)

OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJDIRS := $(sort $(dir $(OBJECTS)))

CFLAGS ?= -O3 -Wall -Wextra -Werror -std=c++11 -pedantic -I$(BUILDDIR) -DNDEBUG
DFLAGS ?= -Wall -Wextra -Werror -std=c++11 -pedantic -I$(BUILDDIR) -g
LFLAGS ?= -lstdc++ -lgmp

TARGET ?= ploy

.PHONY: all dbg clean dirs

all: $(TARGET)

dbg:
	$(eval CFLAGS := $(DFLAGS))
	$(eval export CFLAGS)
	$(MAKE)

clean:
	rm -rf $(OBJDIR) $(BUILDDIR) $(TARGET)

dirs:
	@mkdir -p $(OBJDIRS) $(BUILDDIR)

$(TARGET): dirs $(LIBRARY_OBJECT) $(OBJECTS)
	$(CXX) $(LFLAGS) $(CFLAGS) -o $@ $(LIBRARY_OBJECT) $(OBJECTS)

$(LIBRARY_OBJECT): $(LIBRARY_SOURCE)
	$(CXX) $(CFLAGS) -o $@ -c $<

$(LIBRARY_SOURCE): $(LIBRARY)
	./rc.sh $(LIBRARY) $(BUILDDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<
