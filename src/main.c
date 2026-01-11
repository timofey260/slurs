/*
 SLURS TEST FILE! NOT MEANT TO BE COMPILED WITH SLURS
*/

#include "slurs.h"

int main(int argc, char *argv[]) {
  SetShaderPath("src/assets/textshader.fs", false);
  AddImagePath("src/assets/characters.png", false);
  SlursWindow *window = InitSlurs(32, 16);
  AddStr(window, "Hello, world!", 0, 0, 0);
  RefreshWin(window);
  RunSlurs();
  CloseSlurs();
  return 0;
}
