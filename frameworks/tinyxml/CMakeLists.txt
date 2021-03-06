

cmake_policy(SET CMP0042 NEW)
cmake_policy(SET CMP0048 NEW)

project(tinyxml)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules")

if(MSVC AND NOT EXISTS "${CMAKE_BINARY_DIR}/ALL_BUILD.vcxproj.user")
    file(GENERATE
        OUTPUT "${CMAKE_BINARY_DIR}/ALL_BUILD.vcxproj.user"
        INPUT "${CMAKE_SOURCE_DIR}/CMake/ALL_BUILD.vcxproj.user.in"
        )
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CURRENT_TARGET tinyxml)

set(CURRENT_TARGET_SOURCES
    tinystr.cpp
    tinyxml.cpp
    tinyxmlerror.cpp
    tinyxmlparser.cpp
    xmltest.cpp
    )

set(CURRENT_TARGET_HEADERS
    tinystr.h
    tinyxml.h
    )

include_directories(${CURRENT_TARGET_INCLUDE_DIRECTORIES})

if(WIN32)
    add_library(${CURRENT_TARGET} STATIC
        ${CURRENT_TARGET_SOURCES}
        ${CURRENT_TARGET_HEADERS}
        )
elseif(APPLE)
    add_library(${CURRENT_TARGET} STATIC
        ${CURRENT_TARGET_SOURCES}
        ${CURRENT_TARGET_HEADERS}
        )
elseif(UNIX AND NOT APPLE)
    add_library(${CURRENT_TARGET} STATIC
        ${CURRENT_TARGET_SOURCES} 
        ${CURRENT_TARGET_HEADERS}
        )
endif()

set_target_properties(${CURRENT_TARGET} PROPERTIES COMPILE_FLAGS "-O2 -g -Wall
-std=c++0x")
