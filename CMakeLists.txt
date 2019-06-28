cmake_minimum_required(VERSION 3.0.0)
project(dwm)
# install in ~/.local
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local)

add_subdirectory(3rdparty/next_dwm_status)

add_definitions(-DVERSION="6.2" -std=c99)
add_library(util drw.c util.c)
target_link_libraries(util X11)

include_directories(
    /usr/include/freetype2
)


add_executable(dwm dwm.c)
target_link_libraries(dwm util fontconfig Xft)
install(TARGETS dwm)
