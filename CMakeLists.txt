cmake_minimum_required(VERSION 3.7)

project(FractalGenerator)
set(CMAKE_CXX_STANDARD 14)

#Output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

find_package(Boost)
include_directories(Boost_INCLUDE_DIR)


#Static lib source file definition
set(FGLIB_DIR ${PROJECT_SOURCE_DIR}/src/FractalGenerator)

set(FGLIB_FILES ${FGLIB_DIR}/FractalGenerator.cpp
        ${FGLIB_DIR}/Fractal.cpp
        ${FGLIB_DIR}/Fractals/MandelbrotFractal.cpp src/FractalGenerator/Fractals/FractalTypes.cpp)

add_library(fractalgenerator STATIC ${FGLIB_FILES})
#Static lib end

#Fractal viewer executable definition
set(FV_DIR ${PROJECT_SOURCE_DIR}/src/FractalViewer)

set(FV_FILES ${FV_DIR}/FractalViewer.cpp)

add_executable(FractalViewer ${FV_FILES})
#Link it with the library
target_link_libraries(FractalViewer ${CMAKE_HOME_DIRECTORY}/lib/libfractalgenerator.a)
target_include_directories(FractalViewer PUBLIC ${FGLIB_DIR})
#SFML library include
target_link_libraries(FractalViewer sfml-graphics sfml-window sfml-system)
#Executable end