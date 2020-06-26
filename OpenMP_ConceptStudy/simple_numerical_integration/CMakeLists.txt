###
cmake_minimum_required(VERSION 3.5.1)
project(SimpleNumericalIntegration)
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
add_executable(${PROJECT_NAME}_NumIntNoParallel 00_num_int_no_parallel.cpp)
add_executable(${PROJECT_NAME}_NumIntParallelFalseSharing 01_num_int_paralel_falsesharing.cpp)
add_executable(${PROJECT_NAME}_NumIntParallelNoFalseSharing 02_num_int_paralel_nofalsesharing.cpp)
add_executable(${PROJECT_NAME}_NumIntParallelCriticalSync 03_num_int_paralel_criticalsync.cpp)
add_executable(${PROJECT_NAME}_NumIntParallelAtomicSync 04_num_int_paralel_atomicsync.cpp)
add_executable(${PROJECT_NAME}_NumIntParallelLoopConstruct 05_num_int_paralel_loopconstruct.cpp)
add_executable(${PROJECT_NAME}_NumIntParallelWithSmallestChanges 06_num_int_paralel_withsmallestchanges.cpp)

###
install(TARGETS ${PROJECT_NAME}_NumIntNoParallel DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_NumIntParallelFalseSharing DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_NumIntParallelNoFalseSharing DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_NumIntParallelCriticalSync DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_NumIntParallelAtomicSync DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_NumIntParallelLoopConstruct DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_NumIntParallelWithSmallestChanges DESTINATION bin)

 
