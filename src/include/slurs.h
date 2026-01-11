#ifndef INCLUDEsrcwindowwindow
#define INCLUDEsrcwindowwindow

#include "raylib.h"

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 12
#define SCALE 4
#define FPS 60

#define CHARIMAGE_WIDTH CHAR_WIDTH * 32
#define CHARIMAGE_HEIGHT CHAR_HEIGHT * 16

typedef struct {
  bool dirty;
  int x, y, w, h;
} SlursWindow;

typedef struct {
  int width, height;
  int *characters;
  int character_count;
  Texture character_map;
  Shader text_shader;
  int text_shader_texture_loc;
  int *text_shader_attr_loc;
  int text_shader_CHAR_WIDTH_loc;
  int text_shader_CHAR_HEIGHT_loc;
  int text_shader_DISPLAY_WIDTH_loc;
  int text_shader_DISPLAY_HEIGHT_loc;
  RenderTexture viewport_texture;
  SlursWindow *main_window;
} SlursMainWindow;

typedef struct {
  const char *path;
  bool from_resource;
} FilePath;

void AddImagePath(const char *path, bool fromResource);
void SetShaderPath(const char *path, bool fromResource);
void InitSlurs(int width, int height);
void RunSlurs();
void CloseSlurs();

#endif // INCLUDEsrcwindowwindow.h_
