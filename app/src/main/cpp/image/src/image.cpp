#include "image/image.h"
#include "image/jpeg.h"
#include "image/tiff.h"

namespace image
{
  bool endsWith(std::string str, const std::string& suffix)
  {
    if (suffix.size() > str.size()) return false;
      return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
  }

  void convertJpgToPng(const std::string& filename, const std::string& foldername)
  {
    if(endsWith(filename, "jpeg") || endsWith(filename, "jpg"))
    {
      const auto& imageData = jpegops::decode(filename);
      tiffops::encode(imageData, foldername);
    }
    else
    {
      throw std::runtime_error("Invalid file format!");
    }
  }
}