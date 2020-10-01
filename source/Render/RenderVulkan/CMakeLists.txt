project(RenderVulkan LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC 
            RenderVulkan.cpp
            RenderVulkan.h
)

target_link_libraries(${PROJECT_NAME}
            PUBLIC
                Render
            PRIVATE
                glfw
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR})