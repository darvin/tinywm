/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <stdio.h>
#include <X11/Xlib.h>
#include "xlib.h"

int main(void) {
    XEvent ev;

    if (!openDisplay()) {
        return 1;
    }

    char* keys[] = { "F1", "m", 0 };
    int buttons[] = { 1, 3, 0 };
    grab(keys, buttons);
    setStarted(0);

    while (1) {
        nextEvent(&ev);

        if (ev.type == KeyPress && ev.xkey.subwindow) {
            if (ev.xkey.keycode == 58) {
                getAttr(ev.xkey.subwindow);
                resize(ev.xkey.subwindow, 0, 0, 1800, 1080);
            } else {
                raise(ev.xkey.subwindow);
            }
        } else if (ev.type == ButtonPress && ev.xbutton.subwindow) {
            getAttr(ev.xbutton.subwindow);
            setStart(&ev);
        } else if (ev.type == MotionNotify && isStarted()) {
            handleMotion(&ev);
        } else if (ev.type == ButtonRelease) {
            setStarted(0);
        }
    }
}
