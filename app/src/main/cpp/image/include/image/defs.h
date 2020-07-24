#ifndef DEFS_H
#define DEFS_H

#include <vector>

struct ImageData {
  std::vector<uint8_t> pixels;
  size_t width;
  size_t height;
  uint8_t bytes_per_pixel;
};

#endif