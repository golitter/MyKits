cmake_minimum_required(VERSION 3.0.0)
project(myJSON VERSION 0.1.0)


include_directories(${PROJECT_SOURCE_DIR}/include)

add_definitions("-g -Wall -std=c++11")

add_executable(main
${PROJECT_SOURCE_DIR}/src/main.cpp #这个路径看这个main.cpp位于哪里了
${PROJECT_SOURCE_DIR}/src/myjson.cpp
${PROJECT_SOURCE_DIR}/src/myparser.cpp 
)
