#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "xlib.h"
#include "wm.h"

#define assertEqualsI(a,e) _assertEqualsI(a,e,__FILE__,__LINE__)

static void _assertEqualsI(int actual, int expected, char *file, int line) {
    if (actual == expected) {
        printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m expected %d but got %d\033[0m\n",
               file, line, expected, actual);
    }
}

#define assertFalse(a) _assertTrue(!(a),__FILE__,__LINE__)
#define assertTrue(a) _assertTrue((a),__FILE__,__LINE__)

static void _assertTrue(int actual, char *file, int line) {
    if (actual) {
        printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m got %d\033[0m\n", file, line, actual);
    }
}

static double getElapsedSecondsSince(struct timeval* start) {
    struct timeval now;
    gettimeofday(&now, 0);
    int usec = now.tv_usec - start->tv_usec;
    int sec = now.tv_sec - start->tv_sec;

    return usec * 1e-6 + sec;
}

static int keyEventWindow;
static int mouseEventWindow;
static int windowWidth;
static int raised;
static char* keyPressed;
static int buttonPressed;
static int x, y;

static void setUp(void) {
    keyEventWindow = 0;
    mouseEventWindow = 0;
    windowWidth = 0;
    raised = 0;
    keyPressed = "";
    buttonPressed = 0;
    x = 0;
    y = 0;
}

int openDisplay(void){return 0;}
void grab(char** keys, int* buttons){}
void resize(int window, int left, int top, int width, int height) {
    windowWidth = width;
}

void resizeKeyWindow(int left, int top, int width, int height) {
    windowWidth = width;
}

void raise(int window){raised=window;}

struct coordinates getSize(int window) {
    struct coordinates r = { 100, 100 };
    return r;
}

void nextEvent(void){}
int isKeyPress(void){return 1;}
int isButtonPress(void){return buttonPressed;}
int isMotionNotify(void){return 1;}
int isButtonRelease(void){return 0;}
int getWindowForKeyEvent(void){return keyEventWindow;}
int getWindowForButtonEvent(void){return mouseEventWindow;}
int getButton(void){return buttonPressed;}
int getXRoot(void){return x;}
int getYRoot(void){return y;}
int isKey(char* key){return strcmp(key, keyPressed) == 0;}

static void shouldMaximize(void) {
    setUp();
    keyPressed = "m";
    keyEventWindow = 7;
    processEvent();
    assertTrue(windowWidth > 999);
}

static void shouldRaise(void) {
    setUp();
    keyPressed = "F1";
    keyEventWindow = 7;
    processEvent();
    assertEqualsI(raised, keyEventWindow);
}

static void shouldMove(void) {
    setUp();
    mouseEventWindow = 7;
    buttonPressed = 1;
    x = 300;
    y = 200;
    processEvent();
    buttonPressed = 0;
    processEvent();
    assertEqualsI(windowWidth, 900);
}

static void shouldResize(void) {
    setUp();
    mouseEventWindow = 7;
    buttonPressed = 3;
    x = 100;
    y = 200;
    processEvent();
    buttonPressed = 0;
    processEvent();
    assertEqualsI(windowWidth, 100);
}

int main(void) {
    struct timeval start;
    gettimeofday(&start, 0);

    shouldMaximize();
    shouldRaise();
    shouldMove();
    shouldResize();

    printf("%f seconds\n", getElapsedSecondsSince(&start));

    return 0;
}
