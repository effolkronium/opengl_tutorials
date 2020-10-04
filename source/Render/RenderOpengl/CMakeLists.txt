project(RenderOpengl LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC 
            Window.h
            Window.cpp
   
            RenderOpengl.cpp
            RenderOpengl.h

            Shader.cpp
            Shader.h

            Shaders.h

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

                Utils
)

target_include_directories(${PROJECT_NAME} 
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}
            PRIVATE
                ${CMAKE_SOURCE_DIR}/external/glad_opengl4.6_core/include
)


# Shaders processing

function(make_includable input_file output_path include_file)
    get_filename_component(input_file_name ${input_file} NAME)
    get_filename_component(input_file_name_WLE ${input_file} NAME_WE)

    file(READ ${input_file} content)
    set(delim "for_c++_include")
    set(content "R\"${delim}(\n${content})${delim}\"")
    file(WRITE ${output_path}/${input_file_name} "${content}")

    file(APPEND "Shaders.h" "inline constexpr char* const s_${input_file_name_WLE} = \n"
                             "#include \"${output_path}${input_file_name}\"\n;\n")    
endfunction(make_includable)


file(REMOVE Shaders.h)
file(REMOVE_RECURSE ShadersGen)

file(GLOB SHADERS Shaders/*)

foreach(shader ${SHADERS})
    make_includable(${shader} ShadersGen/ Shaders.h)
endforeach()