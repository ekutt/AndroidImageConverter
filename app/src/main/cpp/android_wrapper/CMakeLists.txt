cmake_minimum_required(VERSION 3.10.2)

include_directories(${CMAKE_SOURCE_DIR}/image/include)

add_library(imageOps-jni
             SHARED
            Image_jni.cpp)

add_library(IMAGELIB SHARED IMPORTED)
set_target_properties(IMAGELIB PROPERTIES IMPORTED_LOCATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libimageOps.so")

target_link_libraries(imageOps-jni PUBLIC IMAGELIB)