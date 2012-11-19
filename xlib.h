int openDisplay(void);
void grab(char** keys, int* buttons);
void resizeKeyWindow(int left, int top, int width, int height);
void raise(int window);
void handleMotion(void);
void getAttr(int window);
void setStarted(int started);
void setStart(void);
int isStarted(void);
void nextEvent(void);
int isKeyPress(void);
int isButtonPress(void);
int isMotionNotify(void);
int isButtonRelease(void);
int getWindowForKeyEvent(void);
int getWindowForButtonEvent(void);
int isKey(char* key);
