#include "slurs.h"
#include <stdlib.h>

extern SlursMainWindow _slurs_window;

SlursWindow *NewWin(int x, int y, int w, int h) {
  SlursWindow *window = malloc(sizeof(SlursWindow));
  *window = (SlursWindow){x, y, w, h, calloc(w * h, sizeof(int)), false, 0};
  return window;
}

void CloseWin(SlursWindow *window) {
  free(window->characters);
  free(window);
}

void ResizeWin(SlursWindow *window, int w, int h) {
  if (_slurs_window.main_window == window)
    return;
  window->characters = realloc(window->characters, sizeof(int) * w * h);
  window->w = w;
  window->h = h;
}

void SetWinAlphachar(SlursWindow *window, int alphachar) {
  window->alphachar = alphachar;
}
