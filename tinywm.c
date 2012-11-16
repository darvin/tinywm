/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <stdio.h>
#include <X11/Xlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static void grab(void* dpy, char** keys, int* buttons) {
    for (int i = 0; keys[i]; ++i) {
        XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym(keys[i])), Mod4Mask,
                 DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
    }

    for (int i = 0; buttons[i]; ++i) {
        XGrabButton(dpy, buttons[i], Mod4Mask, DefaultRootWindow(dpy), True,
                    ButtonPressMask|ButtonReleaseMask|PointerMotionMask,
                    GrabModeAsync, GrabModeAsync, 0, 0);
    }
}

static void resize(void* display, int window, int left, int top, int width, int height) {
    XMoveResizeWindow(display, window, left, top, width, height);
}

static void handleMotion(void* dpy, void* attrp, void* startp, void* evp) {
    XWindowAttributes* attr = attrp;
    XButtonEvent* start = startp;
    XEvent* ev = evp;

    int xdiff = ev->xbutton.x_root - start->x_root;
    int ydiff = ev->xbutton.y_root - start->y_root;
    int isMove = start->button==1;
    int isResize = start->button==3;
    resize(dpy, start->subwindow,
           attr->x + (isMove ? xdiff : 0),
           attr->y + (isMove ? ydiff : 0),
           MAX(1, attr->width + (isResize ? xdiff : 0)),
           MAX(1, attr->height + (isResize ? ydiff : 0)));
}

int main(void)
{
    Display* dpy;
    XWindowAttributes attr;
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
                XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
                XMoveResizeWindow(dpy, ev.xbutton.subwindow,
                                  0, 0, 1800, 1080);
            } else {
                XRaiseWindow(dpy, ev.xkey.subwindow);
            }
        }
        else if(ev.type == ButtonPress && ev.xbutton.subwindow)
        {
            XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
            start = ev.xbutton;
        }
        else if(ev.type == MotionNotify && start.subwindow)
            handleMotion(dpy, &attr, &start, &ev);
        else if(ev.type == ButtonRelease)
        {
            start.subwindow = 0;
        }
    }
}
