PREFIX?=/usr/X11R6
CFLAGS?=-std=gnu11 -Wall -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wpointer-arith -Wcast-qual 

all:
	gcc $(CFLAGS) -Wextra -I$(PREFIX)/include tinywm.c xlib.c wm.c -L$(PREFIX)/lib -lX11 -o tinywm

test:	test.c wm.c
	gcc $(CFLAGS) -I$(PREFIX)/include test.c wm.c -L$(PREFIX)/lib -lX11 -o test

clean:
	rm -f tinywm

