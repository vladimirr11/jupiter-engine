cmake_minimum_required(VERSION 3.12.1)

project(imgui LANGUAGES CXX)

set(_IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}) 

add_library(
    ${PROJECT_NAME} STATIC

        ${_IMGUI_DIR}/imgui.h
        ${_IMGUI_DIR}/imgui.cpp
        ${_IMGUI_DIR}/imconfig.h
        ${_IMGUI_DIR}/imgui_demo.cpp
        ${_IMGUI_DIR}/imgui_draw.cpp
        ${_IMGUI_DIR}/imgui_internal.h
        ${_IMGUI_DIR}/imstb_rectpack.h
        ${_IMGUI_DIR}/imstb_textedit.h
        ${_IMGUI_DIR}/imstb_truetype.h
        ${_IMGUI_DIR}/imgui_tables.cpp
        ${_IMGUI_DIR}/imgui_widgets.cpp

        # bindings
        ${_IMGUI_DIR}/backends/imgui_impl_glfw.h
        ${_IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${_IMGUI_DIR}/backends/imgui_impl_opengl3.h
        ${_IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${_IMGUI_DIR}/backends/imgui_impl_opengl3_loader.h
)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC 
            ${_IMGUI_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PUBLIC 
            glfw
            glad
)
