###
cmake_minimum_required(VERSION 3.5.1)
project(HelloWorld)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_definitions(-std=c++0x -fpermissive)
set(ALL_FOR_BUILD)
set(CMAKE_FIND_DEBUG_MODE 1)

###
find_package(OpenMP REQUIRED)
IF (OPENMP_FOUND)
    message("OPENMP is found")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
ELSE()
    message(FATAL_ERROR "OPENMP is not found")
ENDIF()

###
add_executable(${PROJECT_NAME} hello_world.cpp)

###
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

 
