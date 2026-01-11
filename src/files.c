#include "slurs.h"
#include <stdlib.h>

extern FilePath *_slurs_image_paths;
extern FilePath _slurs_shader_path;
extern int _slurs_images_count;

void AddImagePath(const char *path, bool fromResource) {
  if (_slurs_images_count == 0) {
    _slurs_image_paths = malloc(sizeof(FilePath));
    _slurs_images_count = 1;
  } else {
    _slurs_images_count++;
    _slurs_image_paths =
        realloc(_slurs_image_paths, sizeof(FilePath) * _slurs_images_count);
  }
  _slurs_image_paths[_slurs_images_count - 1] = (FilePath){path, fromResource};
}

void SetShaderPath(const char *path, bool fromResource) {
  _slurs_shader_path.path = path;
  _slurs_shader_path.from_resource = fromResource;
}
