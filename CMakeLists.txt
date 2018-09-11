cmake_minimum_required(VERSION 2.8)

project(fisheye2pano)
add_executable(${PROJECT_NAME} "main.cpp")

find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
