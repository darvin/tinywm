/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include "xlib.h"
#include "wm.h"

int main(void) {
    if (!openDisplay()) {
        return 1;
    }

    grab(getKeys(), getButtons());

    while (1) {
        nextEvent();
        processEvent();
    }
}
