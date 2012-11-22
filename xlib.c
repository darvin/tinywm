#include <X11/Xlib.h>
#include "xlib.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

Display* dpy;
XEvent ev;

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

void resizeKeyWindow(int left, int top, int width, int height) {
    resize(ev.xkey.subwindow, left, top, width, height);
}

void raise(int window) {
    XRaiseWindow(dpy, window);
}

struct coordinates getSize(int window) {
    XWindowAttributes attr;
    XGetWindowAttributes(dpy, window, &attr);
    struct coordinates r = { attr.x, attr.y };
    return r;
}

int getButton(void) {
    return ev.xbutton.button;
}

int getXRoot(void) {
    return ev.xbutton.x_root;
}

int getYRoot(void) {
    return ev.xbutton.y_root;
}

void nextEvent(void) {
    XNextEvent(dpy, &ev);
}

int isKeyPress(void) {
    return ev.type == KeyPress;
}

int isButtonPress(void) {
    return ev.type == ButtonPress;
}

int isMotionNotify(void) {
    return ev.type == MotionNotify;
}

int isButtonRelease(void) {
    return ev.type == ButtonRelease;
}

int getWindowForKeyEvent(void) {
    return ev.xkey.subwindow;
}

int getWindowForButtonEvent(void) {
    return ev.xbutton.subwindow;
}

int isKey(char* key) {
    return ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym(key));
}
