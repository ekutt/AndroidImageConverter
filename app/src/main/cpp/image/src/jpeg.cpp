#include "image/jpeg.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "jpeglib.h"

namespace jpegops
{
  ImageData decode(const std::string& filename)
  {
      int rc, i;
      ImageData imageData;

      // Variables for the source jpg
      struct stat file_info;
      unsigned long jpg_size;
      unsigned char *jpg_buffer;

      // Variables for the decompressor itself
      struct jpeg_decompress_struct cinfo;
      struct jpeg_error_mgr jerr;

      // Variables for the output buffer, and how long each row is
      unsigned long bmp_size;
      unsigned char *bmp_buffer;
      int row_stride;

      rc = stat(filename.c_str(), &file_info);
      if (rc) {
          throw std::runtime_error("Could not stat file " + filename);
      }
      jpg_size = file_info.st_size;
      jpg_buffer = (unsigned char*) malloc(jpg_size + 100);

      int fd = open(filename.c_str(), O_RDONLY);
      i = 0;
      while (i < jpg_size) {
          rc = read(fd, jpg_buffer + i, jpg_size - i);
          i += rc;
      }
      close(fd);

      cinfo.err = jpeg_std_error(&jerr);
      jpeg_create_decompress(&cinfo);

      jpeg_mem_src(&cinfo, jpg_buffer, jpg_size);

      rc = jpeg_read_header(&cinfo, TRUE);

      if (rc != 1) {
          throw std::runtime_error("File does not seem to be a valid jpeg file!");
      }

      jpeg_start_decompress(&cinfo);

      imageData.width = cinfo.output_width;
      imageData.height = cinfo.output_height;
      imageData.bytes_per_pixel = cinfo.output_components;

      bmp_size = imageData.width * imageData.height * imageData.bytes_per_pixel;
      imageData.pixels.resize(bmp_size);

      row_stride = imageData.width * imageData.bytes_per_pixel;

      while (cinfo.output_scanline < cinfo.output_height) {
          unsigned char *buffer_array[1];
          buffer_array[0] = imageData.pixels.data() + \
						   (cinfo.output_scanline) * row_stride;

        jpeg_read_scanlines(&cinfo, buffer_array, 1);
      }

      jpeg_finish_decompress(&cinfo);
      jpeg_destroy_decompress(&cinfo);
      free(jpg_buffer);

      return imageData;
  }
}