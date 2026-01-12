#include "slurs.h"
#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SlursMainWindow _slurs_window;
FilePath *_slurs_image_paths = NULL;
FilePath _slurs_shader_path = {0};
SlursShaderInfo _slurs_shader_info;
int _slurs_images_count = 0;

void ShaderFullClear() {
  int value = 0;
  int ivec2[] = {0, 0};
  int ivec3[] = {0, 0, 0};

  // clearing screen
  for (int i = 0; i < _slurs_window.character_count; i++) {
    SetShaderValue(_slurs_shader_info.text_shader,
                   _slurs_shader_info.text_shader_char_loc[i], &ivec2,
                   SHADER_UNIFORM_IVEC2);
  }
  for (int i = 0; i < COLORS; i++) {
    SetShaderValue(_slurs_shader_info.text_shader,
                   _slurs_shader_info.text_shader_color_loc[i], &ivec3,
                   SHADER_UNIFORM_IVEC3);
  }
  for (int i = 0; i < COLOR_PAIRS; i++) {
    SetShaderValue(_slurs_shader_info.text_shader,
                   _slurs_shader_info.text_shader_colorpair_loc[i], &ivec2,
                   SHADER_UNIFORM_IVEC2);
  }
  float defaultcolor[] = {255, 255, 255};
  SetShaderValue(_slurs_shader_info.text_shader,
                 _slurs_shader_info.text_shader_color_loc[1], &defaultcolor,
                 SHADER_UNIFORM_IVEC3);
  float defaultpair[] = {1, 0};
  SetShaderValue(_slurs_shader_info.text_shader,
                 _slurs_shader_info.text_shader_color_loc[0], &defaultpair,
                 SHADER_UNIFORM_IVEC2);
}

void SetShaderInfo(int width, int height) {
  int character_count = width * height;
  // loading shader
  char str[6]; // just in case
  sprintf(str, "%d", character_count);
  char *text_file = LoadFileText(_slurs_shader_path.path);
  char *shadertext = TextReplace(text_file, "%char_amount%", str);
  _slurs_shader_info.text_shader = LoadShaderFromMemory(NULL, shadertext);
  _slurs_shader_info.text_shader_texture_loc =
      GetShaderLocation(_slurs_shader_info.text_shader, "characters");
  _slurs_shader_info.text_shader_CHAR_SIZE_loc =
      GetShaderLocation(_slurs_shader_info.text_shader, "CHAR_SIZE");
  _slurs_shader_info.text_shader_DISPLAY_SIZE_loc =
      GetShaderLocation(_slurs_shader_info.text_shader, "DISPLAY_SIZE");
  // individual character attributes
  _slurs_shader_info.text_shader_char_loc =
      malloc(sizeof(int) * character_count);
  for (int i = 0; i < character_count; i++) {
    _slurs_shader_info.text_shader_char_loc[i] = GetShaderLocation(
        _slurs_shader_info.text_shader, TextFormat("text_characters[%i]", i));
  }
  for (int i = 0; i < COLORS; i++) {
    _slurs_shader_info.text_shader_color_loc[i] = GetShaderLocation(
        _slurs_shader_info.text_shader, TextFormat("colors[%i]", i));
  }
  for (int i = 0; i < COLOR_PAIRS; i++) {
    _slurs_shader_info.text_shader_colorpair_loc[i] = GetShaderLocation(
        _slurs_shader_info.text_shader, TextFormat("color_pairs[%i]", i));
  }
  UnloadFileText(text_file);

  int char_size[] = {CHAR_WIDTH, CHAR_HEIGHT};
  int display_size[] = {width, height};
  // setting those values
  SetShaderValue(_slurs_shader_info.text_shader,
                 _slurs_shader_info.text_shader_CHAR_SIZE_loc, &char_size,
                 SHADER_UNIFORM_IVEC2);
  SetShaderValue(_slurs_shader_info.text_shader,
                 _slurs_shader_info.text_shader_DISPLAY_SIZE_loc, &display_size,
                 SHADER_UNIFORM_IVEC2);
}

SlursWindow *InitSlurs(int width, int height) {
  InitWindow(width * CHAR_WIDTH * SCALE, height * CHAR_HEIGHT * SCALE,
             "Slurs window");
  Image charmap = GenImageColor(CHARIMAGE_WIDTH, CHARIMAGE_HEIGHT, BLACK);
  for (int i = 0; i < _slurs_images_count; i++) {
    Image img = LoadImage(_slurs_image_paths[i].path);
    Rectangle sourcerect = (Rectangle){0, 0, img.width, img.height};
    ImageDraw(&charmap, img, sourcerect, sourcerect, WHITE);
    UnloadImage(img);
  }

  SetShaderInfo(width, height);

  int character_count = width * height;
  Texture characters_texture = LoadTextureFromImage(charmap);
  _slurs_window =
      (SlursMainWindow){width, height, character_count, characters_texture};
  _slurs_window.main_window = NewWin(0, 0, width, height);
  _slurs_window.viewport_texture =
      LoadRenderTexture(width * CHAR_WIDTH, height * CHAR_HEIGHT);

  _slurs_window.background_color = BLACK;
  UnloadImage(charmap);

  ShaderFullClear();

  return _slurs_window.main_window;
}

void RunSlurs() {
  SetTargetFPS(FPS);
  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginShaderMode(_slurs_shader_info.text_shader);
    SetShaderValueTexture(_slurs_shader_info.text_shader,
                          _slurs_shader_info.text_shader_texture_loc,
                          _slurs_window.character_map);
    DrawTextureEx(_slurs_window.viewport_texture.texture, (Vector2){0, 0}, 0,
                  SCALE, _slurs_window.background_color);
    EndShaderMode();
    // DrawFPS(10, 10);
#ifdef DEBUG
    DrawText("DEBUG MODE", 0, 0, 8, GRAY);
#endif /* ifdef DEBUG */
    EndDrawing();
  }
}

void CloseSlurs() {
  UnloadTexture(_slurs_window.character_map);
  UnloadShader(_slurs_shader_info.text_shader);
  UnloadRenderTexture(_slurs_window.viewport_texture);
  CloseWindow();
}

SlursWindow *GetMainWindow() { return _slurs_window.main_window; }
