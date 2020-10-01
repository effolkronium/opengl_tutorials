project(IRenderCreator LANGUAGES CXX)

add_subdirectory(RenderCreatorOpengl)
add_subdirectory(RenderCreatorVulkan)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME}
            INTERFACE
                IRender
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(RenderCreatorOpengl PROPERTIES FOLDER ${CMAKE_PROJECT_NAME}/Render/${PROJECT_NAME})
set_target_properties(RenderCreatorVulkan PROPERTIES FOLDER ${CMAKE_PROJECT_NAME}/Render/${PROJECT_NAME})