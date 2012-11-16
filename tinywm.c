/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <stdio.h>
#include <X11/Xlib.h>
#include "xlib.h"

int main(void)
{
    void* dpy;
    void* attr = createAttr();
    XButtonEvent start;
    XEvent ev;

    if(!(dpy = XOpenDisplay(0))) return 1;

    char* keys[] = { "F1", "m", 0 };
    int buttons[] = { 1, 3, 0 };
    grab(dpy, keys, buttons);

    start.subwindow = 0;
    for(;;)
    {
        XNextEvent(dpy, &ev);
        if(ev.type == KeyPress && ev.xkey.subwindow) {
            printf("%d\n", ev.xkey.keycode);
            if (ev.xkey.keycode == 58) {
                getAttr(dpy, ev.xbutton.subwindow, attr);
                XMoveResizeWindow(dpy, ev.xbutton.subwindow,
                                  0, 0, 1800, 1080);
            } else {
                XRaiseWindow(dpy, ev.xkey.subwindow);
            }
        }
        else if(ev.type == ButtonPress && ev.xbutton.subwindow)
        {
            getAttr(dpy, ev.xbutton.subwindow, attr);
            start = ev.xbutton;
        }
        else if(ev.type == MotionNotify && start.subwindow)
            handleMotion(dpy, attr, &start, &ev);
        else if(ev.type == ButtonRelease)
        {
            start.subwindow = 0;
        }
    }
}
