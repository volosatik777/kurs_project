set(CURRENT_TARGET executable)

option(ENABLE_UI "Enables the graphics user interface" TRUE)
if(DISABLE_UI)
    message(STATUS "UI disabled")
    return()
elseif(ENABLE_UI)
    set(FIND_MODE REQUIRED)
else()
    set(FIND_MODE QUIET)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

include_directories("${PROJECT_SOURCE_DIR}/src/include")
include_directories("${PROJECT_SOURCE_DIR}/frameworks/EasyBMP/include")
include_directories("${PROJECT_SOURCE_DIR}/frameworks/liblinear-1.94")
include_directories("${PROJECT_SOURCE_DIR}/frameworks/tinyxml")

list(APPEND CURRENT_TARGET_SOURCES
    proj.cpp
    )

list(APPEND CURRENT_TARGET_HEADERS
    new_information.h
    new_step.h
    instruction.h
    parser.h
    )

if (TARGET easybmp)
    list(APPEND CURRENT_TARGET_PLATFORM_LIBRARIES easybmp)
endif()

if (TARGET tinyxml)
    list(APPEND CURRENT_TARGET_PLATFORM_LIBRARIES tinyxml)
endif()

if (TARGET linear)
    list(APPEND CURRENT_TARGET_PLATFORM_LIBRARIES linear)
endif()

if (TARGET argvparser)
    list(APPEND CURRENT_TARGET_PLATFORM_LIBRARIES argvparser)
endif()

include_directories(${CURRENT_TARGET_INCLUDE_DIRECTORIES})

if(WIN32)
    add_executable(${CURRENT_TARGET} WIN32
        ${CURRENT_TARGET_SOURCES}
        ${CURRENT_TARGET_HEADERS}
        )
elseif(APPLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${CURRENT_TARGET})
    add_executable(${CURRENT_TARGET} MACOSX_BUNDLE
        ${CURRENT_TARGET_SOURCES}
        ${CURRENT_TARGET_HEADERS}
        )
elseif(UNIX AND NOT APPLE)
    add_executable(${CURRENT_TARGET}
        ${CURRENT_TARGET_SOURCES}
        ${CURRENT_TARGET_HEADERS}
        )
endif()

set_target_properties(${CURRENT_TARGET} PROPERTIES COMPILE_FLAGS "-O2 -g -std=gnu++11")

target_link_libraries(${CURRENT_TARGET}
    ${CURRENT_TARGET_PLATFORM_LIBRARIES}
    )
