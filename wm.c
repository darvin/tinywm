#include "xlib.h"
#include "wm.h"

static int x_root, y_root;
static int button;
static int subwindow;

static char* keys[] = { "F1", "m", 0 };
static int buttons[] = { 1, 3, 0 };

char** getKeys(void) {
    return keys;
}

int* getButtons(void) {
    return buttons;
}

void processEvent(void) {
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
        int isMove = button==buttons[0];
        int isResize = button==buttons[1];
        resize(subwindow,
               isMove ? getXRoot() : 0,
               isMove ? getYRoot() : 0,
               isResize ? getXRoot() : 900,
               isResize ? getYRoot() : 540);
    } else if (isButtonRelease()) {
        subwindow = 0;
    }
}
