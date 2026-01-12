/*
 SLURS TEST FILE! NOT MEANT TO BE COMPILED WITH SLURS
*/

#include "slurs.h"

int main(int argc, char *argv[]) {
  SetShaderPath("src/assets/textshader.fs", false);
  AddImagePath("src/assets/characters.png", false);
  SlursWindow *window = InitSlurs(32, 16);
  ClearWindow(window, '!', 0);
  AddStr(window,
         "a quick brown fox jumped over a lazy dog\nA QUICK BROWN FOX JUMPED "
         "OVER A LAZY DOG",
         0, 0, 0);
  RefreshWin(window);
  RunSlurs();
  CloseSlurs();
  return 0;
}
