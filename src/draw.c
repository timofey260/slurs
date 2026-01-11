#include "raylib.h"
#include "slurs.h"
#include <string.h>

extern SlursMainWindow _slurs_window;
extern SlursShaderInfo _slurs_shader_info;

int Window2Char(SlursWindow *window, int x, int y) { return x + y * window->w; }

int AddAttr(int ch, CHAR_ATTRIBUTES attr) { return ch + (attr << ATTR_OFFSET); }

void AddStr(SlursWindow *window, const char *text, int x, int y,
            CHAR_ATTRIBUTES attr) {
  int length = strlen(text);
  int winlength = window->w * window->h;
  int newx = x;
  int newy = y;
  for (int i = 0; i < length; i++) {
    int pos = Window2Char(window, newx, newy);
    if (pos >= winlength)
      return;
    window->characters[pos] = AddAttr((int)text[i], attr);
    newx++;
    if (newx >= window->w || text[i] == '\n') {
      newy++;
      newx = x;
    }
  }
}

void RefreshWin(SlursWindow *window) {
  SlursMainWindow mainwindow = _slurs_window;
  for (int x = window->x; x < window->x + window->w && x < mainwindow.width;
       x++) {
    for (int y = window->y; y < window->y + window->h && y < mainwindow.height;
         y++) {
      int windowindex = Window2Char(window, x - window->x, y - window->y);
      int index = Window2Char(window, x, y);
      SetShaderValue(_slurs_shader_info.text_shader,
                     _slurs_shader_info.text_shader_attr_loc[index],
                     &window->characters[windowindex], SHADER_UNIFORM_INT);
    }
  }
}

void ClearWindow(SlursWindow *window, int character) {
  for (int i = 0; i < window->w * window->h; i++) {
    window->characters[i] = character;
  }
}
