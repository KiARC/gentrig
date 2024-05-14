cmake_minimum_required(VERSION 3.28)
project(gentrig VERSION 0.1.0 LANGUAGES C)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})

execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import numpy; print(numpy.get_include())"
    RESULT_VARIABLE NUMPY_NOT_FOUND
    OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(NUMPY_NOT_FOUND)
    message(FATAL_ERROR "NumPy headers not found")
    else()
    message(STATUS "NumPy headers found at: ${NUMPY_INCLUDE_DIR}")
    endif()
include_directories(${NUMPY_INCLUDE_DIR})

add_library(gentrig MODULE gentrig.c)
    
target_link_libraries(gentrig ${Python3_LIBRARIES})
install(TARGETS gentrig LIBRARY DESTINATION gentrig)