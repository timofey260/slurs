#ifndef INCLUDEsrcwindowwindow
#define INCLUDEsrcwindowwindow

#include "raylib.h"
#include <string.h>

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
} SlursMainWindow;

typedef struct {
  const char *path;
  bool from_resource;
} ImagePath;

static SlursMainWindow _slurs_window;
static ImagePath *_slurs_image_paths = NULL;
static int _slurs_images_count = 0;

void AddImagePath(const char *path, bool fromResource);
void InitSlurs(int width, int height);
void RunSlurs();
void CloseSlurs();

#endif // INCLUDEsrcwindowwindow.h_
