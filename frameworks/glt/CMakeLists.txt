

cmake_policy(SET CMP0042 NEW)
cmake_policy(SET CMP0048 NEW)

project(glt)

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

set(CURRENT_TARGET glt)

set(CURRENT_TARGET_SOURCES

glut/capturexfont.c
glut/glut_8x13.c
glut/glut_9x15.c
glut/glut_bitmap.c
glut/glut_bwidth.c
glut/glut_cindex.c
glut/glut_cmap.c
glut/glut_cursor.c
glut/glut_dials.c
glut/glut_dstr.c
glut/glut_event.c
glut/glut_ext.c
glut/glut_fcb.c
glut/glut_fullscrn.c
glut/glut_gamemode.c
glut/glut_get.c
glut/glut_glxext.c
glut/glut_hel10.c
glut/glut_hel12.c
glut/glut_hel18.c
glut/glut_init.c
glut/glut_input.c
glut/glut_joy.c
glut/glut_key.c
glut/glut_keyctrl.c
glut/glut_keyup.c
glut/glut_menu2.c
glut/glut_menu.c
glut/glut_mesa.c
glut/glut_modifier.c
glut/glut_mroman.c
glut/glut_overlay.c
glut/glut_roman.c
glut/glut_shapes.c
glut/glut_space.c
glut/glut_stroke.c
glut/glut_swap.c
glut/glut_swidth.c
glut/glut_tablet.c
glut/glut_teapot.c
glut/glut_tr10.c
glut/glut_tr24.c
glut/glut_util.c
glut/glut_vidresize.c
glut/glut_warp.c
glut/glut_win.c
glut/glut_winmisc.c
glut/layerutil.c
glut/win32_glx.c
glut/win32_menu.c
glut/win32_util.c
glut/win32_winproc.c
glut/win32_x11.c
    )

set(CURRENT_TARGET_HEADERS

    GL/glut.h
    GL/glutf90.h
glut/glutbitmap.h
glut/glutint.h
glut/glutstroke.h
glut/glutwin32.h
glut/layerutil.h
glut/stroke.h
glut/win32_glx.h
glut/win32_x11.h
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
