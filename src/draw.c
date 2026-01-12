#include "raylib.h"
#include "slurs.h"
#include <stdint.h>
#include <string.h>

extern SlursMainWindow _slurs_window;
extern SlursShaderInfo _slurs_shader_info;

int Window2Char(SlursWindow *window, int x, int y) { return x + y * window->w; }

SlursCharacter AddAttr(uint16_t ch, CHAR_ATTRIBUTES attr) {
  return (SlursCharacter){ch, attr};
}

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

int max(int a, int b) { return a > b ? a : b; }

void RefreshWin(SlursWindow *window) {
  SlursMainWindow mainwindow = _slurs_window;
  for (int x = max(0, window->x);
       x < window->x + window->w && x < mainwindow.width; x++) {
    for (int y = max(0, window->y);
         y < window->y + window->h && y < mainwindow.height; y++) {
      int windowindex = Window2Char(window, x - window->x, y - window->y);
      int index = Window2Char(window, x, y);
      SetShaderValue(_slurs_shader_info.text_shader,
                     _slurs_shader_info.text_shader_char_loc[index],
                     &window->characters[windowindex], SHADER_UNIFORM_IVEC2);
    }
  }
}

void ClearWindow(SlursWindow *window, uint16_t character, uint16_t attr) {
  for (int i = 0; i < window->w * window->h; i++) {
    window->characters[i] = (SlursCharacter){character, attr};
  }
}

void SetColor(COLOR_TYPE i, int r, int g, int b) {
  if (i > COLORS - 1 || i < 0)
    return;
  _slurs_window.colors[i] = (SlursColor){r, g, b};
  float color[] = {r / 255.0, g / 255.0, b / 255.0};
  SetShaderValue(_slurs_shader_info.text_shader,
                 _slurs_shader_info.text_shader_color_loc[i], &color,
                 SHADER_UNIFORM_VEC3);
}

void SetColorPair(COLOR_PAIR_TYPE i, COLOR_TYPE fg, COLOR_TYPE bg) {
  if (i > COLOR_PAIRS - 1 || i < 0)
    return;
  _slurs_window.color_pairs[i] = (SlursColorPair){fg, bg};
  int pair[] = {fg, bg};
  SetShaderValue(_slurs_shader_info.text_shader,
                 _slurs_shader_info.text_shader_color_loc[i], &pair,
                 SHADER_UNIFORM_IVEC2);
}
