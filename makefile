
SOURCES=.
OBJDIR=obj
BINDIR=bin
CFLAGS=-I$(SOURCES)

_DEPS=$(wildcard *.h)
DEPS=$(patsubst %,$(SOURCES)/%,$(_DEPS))

SRCFILES=$(wildcard *.c)

_OBJ=$(SRCFILES:c=o)
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

build: clean $(OBJDIR) $(BINDIR) ppmrw

ppmrw: $(OBJ)
	gcc -o $(BINDIR)/$@ $^ -I.

$(OBJDIR)/%.o: %.c $(DEPS)
	gcc -c -o $@ $< -I.

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)