project(RenderCreatorVulkan LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
            RenderCreatorVulkan.h
            RenderCreatorVulkan.cpp
            ../IRenderCreator.h
)

target_link_libraries(${PROJECT_NAME}
            PUBLIC
                IRenderCreator
            PRIVATE
                RenderVulkan
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}
)