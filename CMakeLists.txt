cmake_minimum_required(VERSION 2.6)
project(learnbsp)

set(WIN_CPP_PREFIX_PATH $ENV{WIN_CPP_PREFIX_PATH})
if (NOT WIN_CPP_PREFIX_PATH)
    message("Cannot find WIN_CPP_PREFIX_PATH")
endif()
if (NOT EXISTS "${WIN_CPP_PREFIX_PATH}")
    message("${WIN_CPP_PREFIX_PATH} does not exist")
else()
    set(CMAKE_PREFIX_PATH "${WIN_CPP_PREFIX_PATH}")
    set(CMAKE_MODULE_PATH "${WIN_CPP_PREFIX_PATH}/cmake-modules")
    set(ZLIB_ROOT ${WIN_CPP_PREFIX_PATH})
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
   SET(ENABLE_CXX11 "-std=c++11")

   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()

   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()

if(${CMAKE_BUILD_TYPE} MATCHES DEBUG)
    message(STATUS "CMAKE_BUILD_TYPE: Debug")
else()
    message(STATUS "CMAKE_BUILD_TYPE: Release")
endif(${CMAKE_BUILD_TYPE} MATCHES DEBUG)

find_package(OpenGL REQUIRED)

find_package(GLFW3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})

find_path(GLEXTL
    NAMES GL/glextl.h
    PATHS include
    )
include_directories(${GLEXTL})

add_subdirectory(learnbsp)
