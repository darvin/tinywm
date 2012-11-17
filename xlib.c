#include <X11/Xlib.h>
#include "xlib.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

Display* dpy;
XWindowAttributes attr;
XButtonEvent start;

int openDisplay(void) {
    dpy = XOpenDisplay(0);
    return dpy ? 1 : 0;
}

void grab(char** keys, int* buttons) {
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

void resize(int window, int left, int top, int width, int height) {
    XMoveResizeWindow(dpy, window, left, top, width, height);
}

void raise(int window) {
    XRaiseWindow(dpy, window);
}

void handleMotion(void* evp) {
    XEvent* ev = evp;

    int xdiff = ev->xbutton.x_root - start.x_root;
    int ydiff = ev->xbutton.y_root - start.y_root;
    int isMove = start.button==1;
    int isResize = start.button==3;
    resize(start.subwindow,
           attr.x + (isMove ? xdiff : 0),
           attr.y + (isMove ? ydiff : 0),
           MAX(1, attr.width + (isResize ? xdiff : 0)),
           MAX(1, attr.height + (isResize ? ydiff : 0)));
}

void getAttr(int window) {
    XGetWindowAttributes(dpy, window, &attr);
}

void setStarted(int started) {
    start.subwindow = started;
}

void setStart(void* evp) {
    XEvent* ev = evp;
    start = ev->xbutton;
}

int isStarted(void) {
    return start.subwindow;
}

void nextEvent(void* evp) {
    XNextEvent(dpy, evp);
}
