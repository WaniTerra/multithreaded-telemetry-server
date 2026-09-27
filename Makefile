
CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lpthread

all: panel rocket 

panel: panel.c ringbuffer.c
	$(CC) $(CFLAGS) panel.c ringbuffer.c -o panel $(LIBS)

rocket: rocket.c ringbuffer.c
	$(CC) $(CFLAGS) rocket.c ringbuffer.c -o rocket $(LIBS)

clean:
	rm -f panel rocket