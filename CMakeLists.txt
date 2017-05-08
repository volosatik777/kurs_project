cmake_minimum_required(VERSION 2.8.12)

cmake_policy(SET CMP0042 NEW)
cmake_policy(SET CMP0048 NEW)

project(Application)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules")

if(MSVC AND NOT EXISTS "${CMAKE_BINARY_DIR}/ALL_BUILD.vcxproj.user")
    file(GENERATE
        OUTPUT "${CMAKE_BINARY_DIR}/ALL_BUILD.vcxproj.user"
        INPUT "${CMAKE_SOURCE_DIR}/CMake/ALL_BUILD.vcxproj.user.in"
        )
endif()

if (NOT TARGET easybmp)
    add_subdirectory(frameworks/EasyBMP)
endif()

if (NOT TARGET tinyxml)
    add_subdirectory(frameworks/tinyxml)
endif()

if (NOT TARGET glt)
    add_subdirectory(frameworks/glt)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

add_subdirectory(src)
