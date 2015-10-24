CC=gcc
CFLAGS=-c
LDFLAGS=
SOURCES= main.c \
		 dir.c \
		 my_ftw.c

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= find_files

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(PROGRAMS) *.o core
	@rm -f $(EXECUTABLE)
