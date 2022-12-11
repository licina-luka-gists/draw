#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[]) {
  Display *display;
  Window window;
  XEvent event;
  char *msg = "Lorem ipsum";
  int scr;

  display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  scr = DefaultScreen(display);

  window = XCreateSimpleWindow(display,
			       RootWindow(display, scr),
			       10,
			       10,
			       100,
			       100,
			       1,
			       BlackPixel(display, scr),
			       WhitePixel(display, scr));

  XSelectInput(display, window, ExposureMask | KeyPressMask);

  XMapWindow(display, window);

  while (1) {
    XNextEvent(display, &event);

    if (event.type == KeyPress) {
      break;
    }

    if (event.type == Expose) {
      XFillRectangle(display, window, DefaultGC(display, scr), 20, 20, 10, 10);
      XDrawString(display, window, DefaultGC(display, scr), 10, 50, msg, strlen(msg));
    }

  }
    XCloseDisplay(display);
    return 0;
}
