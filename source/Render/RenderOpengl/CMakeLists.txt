project(RenderOpengl LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC 
            RenderOpengl.cpp
            RenderOpengl.h
)

target_link_libraries(${PROJECT_NAME}
            PUBLIC
                Render
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR})