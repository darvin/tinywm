PREFIX?=/usr/X11R6
CFLAGS?=-std=gnu++0x -pedantic -Wall

all:
	g++ $(CFLAGS) -I$(PREFIX)/include tinywm.c -L$(PREFIX)/lib -lX11 -o tinywm

clean:
	rm -f tinywm

