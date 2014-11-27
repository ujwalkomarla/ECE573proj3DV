CC=gcc
CFLAGS=-c -Wall -g 
LDFLAGS= -pthread
SOURCES=
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o $(EXECUTABLE)
