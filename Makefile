CC := gcc
SRCDIR := src
BUILDDIR := build
BINDIR := ./bin/lib
SHAREDDIR := ./bin/lib
SHAREDINC := ./bin/include/compress
TARGET := coder
LIBS := ./bin/lib/libicompress.a
SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS :=  
LIB := -L./bin/lib -lopenjpeg -licompress
INC := -I./bin/include
SUBDIRS := openjpeg

all: jpeg lib $(TARGET) decoder

jpeg:
	make -C openjpeg install

$(TARGET): compress.c
	$(CC) $^ -o $(TARGET) $(LIB) $(INC)

$(LIBS): $(OBJECTS)
	if [ ! -d "$(SHAREDDIR)" ];then mkdir -p $(SHAREDDIR); fi;
	if [ ! -d "$(SHAREDINC)" ];then mkdir -p $(SHAREDINC); fi;
	cp -R src/*.h $(SHAREDINC)
	ar rcs $@ $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	if [ ! -d "$(BUILDDIR)" ];then mkdir $(BUILDDIR); fi
	$(CC) $(CFLAGS) -c -o $@ $< $(INC)

lib: $(LIBS)

decoder: decompress.c
	$(CC) $^ -o decoder $(LIB) $(INC)

clean:
	$(RM) -r $(BUILDDIR) $(SHAREDINC) $(BINDIR) coder decoder  test *.o
	make -C openjpeg clean
	
.PHONY: clean