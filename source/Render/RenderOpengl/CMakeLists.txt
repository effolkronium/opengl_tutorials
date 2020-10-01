project(RenderOpengl LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC 
            RenderOpengl.cpp
            RenderOpengl.h
            ${CMAKE_SOURCE_DIR}/external/glad/src/gl.c
)

target_link_libraries(${PROJECT_NAME}
            PUBLIC
                Render
            PRIVATE
                glfw
                glm
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}
            PRIVATE
                ${CMAKE_SOURCE_DIR}/external/glad/include
)