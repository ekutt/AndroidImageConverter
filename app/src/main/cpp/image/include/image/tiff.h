#ifndef IMAGE_CONVERTER_TIFF_H
#define IMAGE_CONVERTER_TIFF_H

#include <string>
#include <vector>
#include "defs.h"

namespace tiffops
{
  void encode(const ImageData& imageData, const std::string& outputFilename);
};

#endif //IMAGE_CONVERTER_PNG_H