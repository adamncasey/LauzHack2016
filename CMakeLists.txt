cmake_minimum_required(VERSION 2.8)
project(Lauzhack)
set(CMAKE_BUILD_TYPE Release)
find_package(OpenCV REQUIRED)

add_definitions(-std=c++11)

#add_subdirectory(${Lauzhack_SOURCE_DIR}/src)

include_directories(${OpenCV_INCLUDE_DIRS})
                    
add_executable(main ${Lauzhack_SOURCE_DIR}/src/main.cpp)
target_link_libraries(main ${OpenCV_LIBS})
