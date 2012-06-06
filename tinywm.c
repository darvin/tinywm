/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <X11/Xlib.h>

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

class Tiny {
    Display * dpy;
    XWindowAttributes attr;

 public:
    Tiny(Display* dpy) {
        this->dpy = dpy;
    };

    unsigned int key(const char* name) {
        return XKeysymToKeycode(dpy, XStringToKeysym(name));
    }

    void grabButton(int button, int mask) {
        XGrabButton(dpy, button, mask, DefaultRootWindow(dpy), True,
                    ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
    }

    void grab() {
        XGrabKey(dpy, key("F1"), Mod1Mask,
                 DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
        XGrabKey(dpy, key("r"), Mod4Mask,
                 DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);

        grabButton(1, Mod4Mask);
        grabButton(3, Mod4Mask);
    }

    void handleEvent(XEvent& ev, XButtonEvent& start) {
        if(ev.type == KeyPress && ev.xkey.subwindow != None)
            XRaiseWindow(dpy, ev.xkey.subwindow);
        else if(ev.type == ButtonPress && ev.xbutton.subwindow != None)
        {
            XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
            start = ev.xbutton;
        }
        else if(ev.type == MotionNotify && start.subwindow != None)
        {
            int xdiff = ev.xbutton.x_root - start.x_root;
            int ydiff = ev.xbutton.y_root - start.y_root;
            XMoveResizeWindow(dpy, start.subwindow,
                attr.x + (start.button==1 ? xdiff : 0),
                attr.y + (start.button==1 ? ydiff : 0),
                MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
                MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
        }
        else if(ev.type == ButtonRelease)
        {
            start.subwindow = None;
        }
    }
};

int main(void)
{
    Display * dpy = XOpenDisplay(0x0);
    XButtonEvent start;
    XEvent ev;

    if (!dpy) {
        return 1;
    }

    Tiny wm(dpy);

    wm.grab();

    start.subwindow = None;
    for(;;)
    {
        XNextEvent(dpy, &ev);
        wm.handleEvent(ev, start);
    }
}
