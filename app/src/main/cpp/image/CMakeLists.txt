cmake_minimum_required(VERSION 3.10.2)

include_directories("${CMAKE_SOURCE_DIR}/image/include")
include_directories("${CMAKE_SOURCE_DIR}/../../../../3rd-party/jpeg-9d/include")
include_directories("${CMAKE_SOURCE_DIR}/../../../../3rd-party/tiff-4.1.0/include")

add_library(imageOps
             SHARED
             src/tiff.cpp
             src/jpeg.cpp
             src/image.cpp)

add_library(ZLIB SHARED IMPORTED)
set_target_properties(ZLIB PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libz.so")

add_library(JPEGLIB SHARED IMPORTED)
set_target_properties(JPEGLIB PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libjpeg.so")

add_library(TIFFLIB SHARED IMPORTED)
set_target_properties(TIFFLIB PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libtiff.so")

target_link_libraries(imageOps PUBLIC JPEGLIB)
target_link_libraries(imageOps PUBLIC TIFFLIB)
target_link_libraries(imageOps PUBLIC ZLIB)