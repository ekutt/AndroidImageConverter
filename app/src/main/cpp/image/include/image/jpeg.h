#ifndef IMAGE_CONVERTER_JPEG_H
#define IMAGE_CONVERTER_JPEG_H

#include <string>
#include <vector>
#include "defs.h"

namespace jpegops
{
  ImageData decode(const std::string& filename);
};

#endif //IMAGE_CONVERTER_JPEG_H