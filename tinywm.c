/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <stdio.h>
#include "xlib.h"

int main(void) {
    if (!openDisplay()) {
        return 1;
    }

    char* keys[] = { "F1", "m", 0 };
    int buttons[] = { 1, 3, 0 };
    grab(keys, buttons);
    setStarted(0);

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
            getAttr(getWindowForButtonEvent());
            setStart();
        } else if (isMotionNotify() && isStarted()) {
            handleMotion();
        } else if (isButtonRelease()) {
            setStarted(0);
        }
    }
}
