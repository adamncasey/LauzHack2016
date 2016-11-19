cmake_minimum_required(VERSION 2.8)
project(Lauzhack)
set(CMAKE_BUILD_TYPE Release)
find_package(OpenCV REQUIRED)

add_definitions(-std=c++14)

#add_subdirectory(${Lauzhack_SOURCE_DIR}/src)

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${Lauzhack_SOURCE_DIR}/src)
include_directories(${Lauzhack_SOURCE_DIR}/include)
                    
<<<<<<< HEAD
add_executable(main ${Lauzhack_SOURCE_DIR}/src/main.cpp 
		    ${Lauzhack_SOURCE_DIR}/src/calibrate.cpp 
	            ${Lauzhack_SOURCE_DIR}/src/colour.cpp 
	            ${Lauzhack_SOURCE_DIR}/src/keyboard/Flasher.cpp)
=======
add_executable(main ${Lauzhack_SOURCE_DIR}/src/main.cpp ${Lauzhack_SOURCE_DIR}/src/calibrate.cpp ${Lauzhack_SOURCE_DIR}/src/keyboard/Flasher.cpp ${Lauzhack_SOURCE_DIR}/src/calibrateColors.cpp)
>>>>>>> ae476131def1af8c46df79fadfe54b45eaa55e53

target_link_libraries(main ${OpenCV_LIBS})

if(NOT UNIX)
    target_link_libraries(main lib_win64/LogitechLEDLib)
endif()
