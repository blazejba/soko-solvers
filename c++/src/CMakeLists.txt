project(ai_solver)
cmake_minimum_required(VERSION 3.22)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ai_solver.cpp)