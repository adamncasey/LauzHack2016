cmake_minimum_required(VERSION 2.8)
project(Lauzhack)
set(CMAKE_BUILD_TYPE Release)
find_package(OpenCV REQUIRED)

add_definitions(-std=c++14)

#add_subdirectory(${Lauzhack_SOURCE_DIR}/src)

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${Lauzhack_SOURCE_DIR}/src)
include_directories(${Lauzhack_SOURCE_DIR}/include)
                    
add_executable(main ${Lauzhack_SOURCE_DIR}/src/main.cpp )

target_link_libraries(main ${OpenCV_LIBS} pthread)
if(NOT UNIX)
	target_link_libraries(main ${Lauzhack_SOURCE_DIR}/lib_win64/LogitechLEDLib.lib)
endif()
