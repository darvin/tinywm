void grab(void* dpy, char** keys, int* buttons);
void resize(void* display, int window, int left, int top, int width, int height);
void handleMotion(void* dpy, void* attrp, void* startp, void* evp);
void getAttr(void* dpy, int window, void* attrp);
void* createAttr(void);
