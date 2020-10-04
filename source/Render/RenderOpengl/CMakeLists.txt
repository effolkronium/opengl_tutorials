project(RenderOpengl LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC 
            RenderOpengl.cpp
            RenderOpengl.h
            ../IRender.h

            ${CMAKE_SOURCE_DIR}/external/glad_opengl4.6_core/src/glad.c
)

target_link_libraries(${PROJECT_NAME}
            PUBLIC
                IRender
            PRIVATE
                OpenGL::GL
                glfw
                glm
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}
            PRIVATE
                ${CMAKE_SOURCE_DIR}/external/glad_opengl4.6_core/include
)