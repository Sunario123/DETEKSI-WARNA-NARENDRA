cmake_minimum_required(VERSION 3.0)

project( oprec )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package( OpenCV REQUIRED )

add_executable( oprec src/kalibrasi_kamera.cpp)

target_link_libraries( oprec ${OpenCV_LIBS} )