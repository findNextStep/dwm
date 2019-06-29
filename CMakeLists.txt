cmake_minimum_required(VERSION 3.0.0)
project(dwm)
# install in ~/.local
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local)

add_subdirectory(3rdparty/next_dwm_status)
add_subdirectory(3rdparty/st)
add_subdirectory(3rdparty/dmenu)

add_definitions(-DVERSION="6.2" -std=c99 -DXINERAMA)
add_library(dwm_util drw.c util.c)
target_link_libraries(dwm_util X11)

include_directories(
    /usr/include/freetype2
)


add_executable(dwm dwm.c)
target_link_libraries(dwm dwm_util fontconfig Xft Xinerama X11)
install(TARGETS dwm)
