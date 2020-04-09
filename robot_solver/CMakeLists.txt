cmake_minimum_required(VERSION 2.8)
project( robot_solver )
find_package( OpenCV 3 REQUIRED )
add_executable(robot_solver src/main.cpp )
target_link_libraries( robot_solver ${OpenCV_LIBS})

