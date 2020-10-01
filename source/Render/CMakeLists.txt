project(Render LANGUAGES CXX)

add_subdirectory(IRender)
add_subdirectory(RenderOpengl)
add_subdirectory(RenderVulkan)
add_subdirectory(RenderCreator)

add_library(${PROJECT_NAME} STATIC 
            Render.h
            Render.cpp
            IRender/IRender.h
)

target_link_libraries(${PROJECT_NAME} 
            PUBLIC
                IRender
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${CMAKE_PROJECT_NAME}/${PROJECT_NAME})
set_target_properties(RenderOpengl PROPERTIES FOLDER ${CMAKE_PROJECT_NAME}/${PROJECT_NAME})
set_target_properties(RenderVulkan PROPERTIES FOLDER ${CMAKE_PROJECT_NAME}/${PROJECT_NAME})