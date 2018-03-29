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
LIB := -L./bin/lib -L/usr/local/lib -licompress -lopenjpeg
INC := -I./bin/include

all: openjpeg lib $(TARGET) decoder

openjpeg:
	make -C openjpeg
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
	$(RM) -r $(BUILDDIR) $(SHAREDINC) $(BINDIR)/libicompress.so $(BINDIR)/libicompress.a  test *.o
	
.PHONY: clean