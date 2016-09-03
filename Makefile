CXX := clang

SRCDIR := src
OBJDIR := obj
BUILDDIR := build

SOURCES := $(shell find $(SRCDIR) -name '*.cpp')

LIBRARY := $(SRCDIR)/library.scm
LIBRARY_SOURCE := $(LIBRARY:$(SRCDIR)/%.scm=$(BUILDDIR)/%.cpp)
LIBRARY_HEADER := $(LIBRARY_SOURCE:.cpp=.h)
LIBRARY_OBJECT := $(LIBRARY_SOURCE:$(BUILDDIR)/%.cpp=$(OBJDIR)/%.o)

OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJDIRS := $(sort $(dir $(OBJECTS)))

CFLAGS ?= -O3 -Wall -Wextra -Werror -std=c++11 -pedantic -I$(BUILDDIR) -DNDEBUG
DFLAGS ?= -Wall -Wextra -Werror -std=c++11 -pedantic -I$(BUILDDIR) -g
LFLAGS ?= -lstdc++ -lgmp

TARGET ?= ploy

.PHONY: all dbg clean

all: $(TARGET)

dbg:
	$(eval CFLAGS := $(DFLAGS))
	$(eval export CFLAGS)
	$(MAKE)

$(TARGET): $(LIBRARY_OBJECT) $(OBJECTS)
	$(CXX) $(LFLAGS) $(CFLAGS) -o $@ $(LIBRARY_OBJECT) $(OBJECTS)

$(LIBRARY_OBJECT): $(LIBRARY_SOURCE) $(OBJDIR)
	$(CXX) $(CFLAGS) -o $@ -c $<

$(LIBRARY_SOURCE): $(LIBRARY) $(BUILDDIR)
	./rc.sh $(LIBRARY) $(BUILDDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR)
	$(CXX) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	mkdir -p $(OBJDIRS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(OBJDIR) $(BUILDDIR) $(TARGET)
