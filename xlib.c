#include <X11/Xlib.h>
#include "xlib.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void grab(void* dpy, char** keys, int* buttons) {
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

void resize(void* display, int window, int left, int top, int width, int height) {
    XMoveResizeWindow(display, window, left, top, width, height);
}

void handleMotion(void* dpy, void* attrp, void* startp, void* evp) {
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

void getAttr(void* dpy, int window, void* attrp) {
    XGetWindowAttributes(dpy, window, attrp);
}

XWindowAttributes attr;

void* createAttr(void) {
    return &attr;
}
