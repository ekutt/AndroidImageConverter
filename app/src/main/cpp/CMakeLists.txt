cmake_minimum_required(VERSION 3.10.2)

#Build native library
add_subdirectory(image)

#Build android wrapper
add_subdirectory(android_wrapper)