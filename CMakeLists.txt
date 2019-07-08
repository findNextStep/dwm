cmake_minimum_required(VERSION 3.0.0)
project(dwm)
# install in ~/.local
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local)

find_package(Git QUIET)
function(add_git_submodule dir)
    
    if(GIT_FOUND)
        message(STATUS "git found: ${GIT_EXECUTABLE}-v${GIT_VERSION_STRING}")
        message(STATUS "start submodule update")
        # 下载git子模块
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init ${dir}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            # 下载失败的处理
            message(WARNING "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        else()
            add_subdirectory(${dir})
        endif()
    endif()
endfunction(add_git_submodule)


add_git_submodule(3rdparty/next_dwm_status)
add_git_submodule(3rdparty/st)
add_git_submodule(3rdparty/dmenu)

include_directories(3rdparty/next_dwm_status/include)

add_library(dwm_util drw.c util.c)
target_compile_options(dwm_util PRIVATE -std=c99 -DXINERAMA)
target_link_libraries(dwm_util X11)

include_directories(
    /usr/include/freetype2
)


add_executable(dwm dwm.c)
target_compile_options(dwm PRIVATE -DVERSION="6.2" -std=c99 -DXINERAMA)
target_link_libraries(dwm dwm_util fontconfig Xft Xinerama X11 util_volume)
install(TARGETS dwm)
