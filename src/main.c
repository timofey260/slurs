/*
 SLURS TEST FILE! NOT MEANT TO BE COMPILED WITH SLURS
*/

#include "slurs.h"

int main(int argc, char *argv[]) {
  SetShaderPath("src/assets/textshader.fs", false);
  AddImagePath("src/assets/characters.png", false);
  InitSlurs(32, 16);
  RunSlurs();
  CloseSlurs();
  return 0;
}
