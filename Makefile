CC= gcc
CCFLAGS=-O0 -Wall -I./ 

SOURCES= $(wildcard */*.c)
TARGET= $(subst .c,,$(SOURCES))

all: $(TARGET)

$(TARGET):
	$(CC) $(CCFLAGS) -o $@ $@.c

clean:
	rm $(TARGET)
