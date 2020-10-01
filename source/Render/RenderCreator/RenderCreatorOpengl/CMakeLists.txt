project(RenderCreatorOpengl LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
            RenderCreatorOpengl.h
            RenderCreatorOpengl.cpp
            ../IRenderCreator.h
)

target_link_libraries(${PROJECT_NAME}
            PUBLIC
                IRenderCreator
            PRIVATE
                RenderOpengl
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}
)