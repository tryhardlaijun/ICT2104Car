# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)


# Set name of project (as PROJECT_NAME) and C/C++ standards
project(mapping C CXX ASM )
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(
    wjLai
    movement.c
    map.c
    file.c
    coordinate.c
    sensedData.txt
)
# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
    main.c
)
INCLUDE_DIRECTORIES(${PROJECT_NAME})
 target_link_libraries(${PROJECT_NAME} wjLai
 )

 file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sensedData.txt
 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
