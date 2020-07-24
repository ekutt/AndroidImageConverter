#include "image/tiff.h"
#include "image/defs.h"
#include "tiffio.h"

namespace tiffops
{
  void encode(const ImageData& imageData, const std::string& outputFilename)
  {
    TIFF *image = TIFFOpen(outputFilename.c_str(), "w");

    if(!image)
    {
       throw std::runtime_error("Cannot open TIFF file!");
    }

    TIFFSetField(image, TIFFTAG_IMAGEWIDTH, imageData.width);
    TIFFSetField(image, TIFFTAG_IMAGELENGTH, imageData.height);
    TIFFSetField(image, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(image, TIFFTAG_SAMPLESPERPIXEL, 3);
    TIFFSetField(image, TIFFTAG_ROWSPERSTRIP, 1);
    TIFFSetField(image, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(image, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(image, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
    TIFFSetField(image, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
    TIFFSetField(image, TIFFTAG_COMPRESSION, COMPRESSION_LZW);

    uint8_t* scan_line = (uint8_t*)malloc(imageData.width*(sizeof(uint8_t))*3);

    for (int heightIndex = 0; heightIndex < imageData.height; heightIndex++)
    {
      for (int widthIndex = 0; widthIndex < imageData.width; widthIndex++)
      {
        scan_line[widthIndex*3] = imageData.pixels.data()[imageData.width*3*heightIndex+widthIndex*3];
        scan_line[widthIndex*3+1] = imageData.pixels.data()[imageData.width*3*heightIndex+widthIndex*3+1];
        scan_line[widthIndex*3+2] = imageData.pixels.data()[imageData.width*3*heightIndex+widthIndex*3+2];
      }

      if(TIFFWriteScanline(image, scan_line, heightIndex, 0) !=  1)
      {
        throw std::runtime_error("Error With TIFFWriteScanline!");
      }
    }

    TIFFClose(image);
    free(scan_line);
  }
};

