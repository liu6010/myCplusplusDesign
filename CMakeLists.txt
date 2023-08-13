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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    # add_definitions(-fsanitize=address)
    # add_definitions(-fno-omit-frame-pointer)
    
endif()
message(STATUS "BUILD TYPE:" ${CMAKE_BUILD_TYPE})

include_directories(${PROJECT_SOURCE_DIR})



option(ENABLE_MyDesign "Enable MyDesign subdirectory" TRUE)
option(ENABLE_algorithm "Enable algorithm subdirectory" TRUE)
option(ENABLE_thread "Enable thread subdirectory" TRUE)
option(ENABLE_DesignModel "Enable DesignModel subdirectory" TRUE)

# enable_testing()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(ENABLE_MyDesign)
    message(STATUS "Enable MyDesign Module")
    add_subdirectory(MyDesign)
endif()

if(ENABLE_algorithm)
    message(STATUS "Enable algorithm Module")
    add_subdirectory(algorithm)
endif()

if(ENABLE_thread)
    message(STATUS "Enable thread Module")
    add_subdirectory(thread)

endif()

if(ENABLE_DesignModel)
    message(STATUS "Enable DesignModel Module")
    add_subdirectory(DesignModel)
endif()


