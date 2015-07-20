CC=gcc
CFLAGS=-c
LDFLAGS=
SOURCES= main.c \
		 dir.c \
		 my_ftw.c

OBJECTS=$(SOURCES:.cpp=.0)
EXECUTABLE= find_files

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(PROGRAMS) *.o core
	@rm -f $(EXECUTABLE)
