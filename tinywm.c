/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <stdio.h>
#include "xlib.h"

static int x_root, y_root;
static int button;
static int subwindow;

int main(void) {
    if (!openDisplay()) {
        return 1;
    }

    char* keys[] = { "F1", "m", 0 };
    int buttons[] = { 1, 3, 0 };
    grab(keys, buttons);
    subwindow = 0;

    while (1) {
        nextEvent();

        if (isKeyPress() && getWindowForKeyEvent()) {
            if (isKey(keys[1])) {
                getAttr(getWindowForKeyEvent());
                resizeKeyWindow(0, 0, 1800, 1080);
            } else {
                raise(getWindowForKeyEvent());
            }
        } else if (isButtonPress() && getWindowForButtonEvent()) {
            subwindow = getWindowForButtonEvent();
            button = getButton();
            x_root = getXRoot();
            y_root = getYRoot();
        } else if (isMotionNotify() && subwindow) {
            int xdiff = getXRoot() - x_root;
            int ydiff = getYRoot() - y_root;
            int isMove = button==1;
            int isResize = button==3;
            resize(subwindow,
                   isMove ? getXRoot() : 0,
                   isMove ? getYRoot() : 0,
                   isResize ? getXRoot() : 900,
                   isResize ? getYRoot() : 540);
        } else if (isButtonRelease()) {
            subwindow = 0;
        }
    }
}
