#ifndef INCLUDEsrcwindowwindow
#define INCLUDEsrcwindowwindow

#include "raylib.h"
#include <stdint.h>

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 12
#define SCALE 4
#define FPS 60
#define ATTR_OFFSET (16 - ATTR_COUNT)

#define COLORS 256
#define COLOR_PAIRS 256
#define COLOR_TYPE char
#define COLOR_PAIR_TYPE char

#define CHARIMAGE_WIDTH CHAR_WIDTH * 32
#define CHARIMAGE_HEIGHT CHAR_HEIGHT * 16

typedef enum {
  ATTR_BOLD = 1,
  ATTR_DIM = 1 << 1,
  ATTR_BLINK = 1 << 2,
  ATTR_ITALIC = 1 << 3,
  ATTR_COUNT = 4
} CHAR_ATTRIBUTES;

typedef struct {
  uint16_t character;
  uint16_t attribute;
} SlursCharacter;

typedef struct {
  int x, y, w, h;
  SlursCharacter *characters;
  bool dirty;
  int alphachar;
} SlursWindow;

typedef struct {
  int r, g, b;
} SlursColor;

typedef struct {
  COLOR_TYPE fg;
  COLOR_TYPE bg;
} SlursColorPair;

typedef struct {
  int width, height;
  int character_count;
  Texture character_map;
  RenderTexture viewport_texture;
  SlursWindow *main_window;
  Color background_color;
  SlursColor colors[COLORS];
  SlursColorPair color_pairs[COLOR_PAIRS];
} SlursMainWindow;

typedef struct {
  Shader text_shader;
  int text_shader_texture_loc;
  int *text_shader_char_loc;
  int text_shader_color_loc[COLORS];
  int text_shader_colorpair_loc[COLOR_PAIRS];
  int text_shader_CHAR_SIZE_loc;
  int text_shader_DISPLAY_SIZE_loc;
} SlursShaderInfo;

typedef struct {
  const char *path;
  bool from_resource;
} FilePath;

// files.c

// Add path to character image
//
// When image path gets added,
// on InitSlurs it will load all images
// into one that will then be passed into shader
//
// NOTE: This function should be called BEFORE InitSlurs
void AddImagePath(const char *path, bool fromResource);
// Change shader path, allows for custom character shader
void SetShaderPath(const char *path, bool fromResource);

// slurs.c

// Initiate Slurs engine
//
// NOTE: This function should be called BEFORE InitSlurs
SlursWindow *InitSlurs(int width, int height);
// Runs slurs's update loop
void RunSlurs();
// Close slurs engine and unload all assets
void CloseSlurs();
// Returns main slurs window
SlursWindow *GetMainWindow();

// draw.c

// Draws str on specified window
void AddStr(SlursWindow *window, const char *text, int x, int y,
            CHAR_ATTRIBUTES attr);
// Converts from window position to character position
//
// NOTE: Does not prevent going outside of characters array
// so can access unallocated memory
int Window2Char(SlursWindow *window, int x, int y);
// Adds attribute to character
SlursCharacter AddAttr(uint16_t ch, CHAR_ATTRIBUTES attr);
// Update shader values to screen ones
void RefreshWin(SlursWindow *window);
// Clear window to specified character
//
// Does not refresh screen
void ClearWindow(SlursWindow *window, uint16_t character, uint16_t attr);
// Set Slurs's color
//
// NOTE: There is hard limit to COLORS different colors
void SetColor(COLOR_TYPE i, int r, int g, int b);
// Set Slurs color pair
//
// NOTE: There is hard  limit to COLOR_PAIRS different color pairs
void SetColorPair(COLOR_PAIR_TYPE i, COLOR_TYPE fg, COLOR_TYPE bg);

// window.c

// Create new window
SlursWindow *NewWin(int x, int y, int w, int h);
// Close window and free window memory
//
// NOTE: Closing main window will result in a crash or undefined behavior
void CloseWin(SlursWindow *window);
// Resize window
//
// NOTE: Resizing main window is prohibited
void ResizeWin(SlursWindow *window, int w, int h);
// Set window's alpha character
//
// Window alpha character is a character that doesn't update screens character
//
// Setting character to 0 makes all characters opaque
void SetWinAlphachar(SlursWindow *window, int alphachar);

#endif // INCLUDEsrcwindowwindow.h_
