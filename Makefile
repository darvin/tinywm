PREFIX?=/usr/X11R6
CFLAGS?=-std=gnu11 -Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wpointer-arith -Wcast-qual 

all:
	gcc $(CFLAGS) -I$(PREFIX)/include tinywm.c xlib.c wm.c -L$(PREFIX)/lib -lX11 -o tinywm

clean:
	rm -f tinywm

