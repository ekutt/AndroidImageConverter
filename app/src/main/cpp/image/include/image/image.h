#ifndef IMAGE_CONVERTER_IMAGE_H
#define IMAGE_CONVERTER_IMAGE_H

#include <string>
#include "defs.h"

namespace image
{
    __attribute__((visibility("default"))) void convertJpgToPng(const std::string& filename, const std::string& foldername);
};

#endif