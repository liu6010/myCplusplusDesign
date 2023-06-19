cmake_minimum_required(VERSION 3.2)
project (myCplusplusDesign CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModuls)


if(CMAKE_VERSION VERSION_LESS "3")
    add_definitions(-std=c++14)
else()
    # add_definitions(-std=c++14)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
    # set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("BUILD TYPE:" ${CMAKE_BUILD_TYPE})

include_directories(${PROJECT_SOURCE_DIR})

# enable_testing()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(MyDesign)
add_subdirectory(algorithm)
add_subdirectory(thread)
add_subdirectory(DesignModel)

