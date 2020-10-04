#pragma once

#include <string>
#include <filesystem>
#include "glad/glad.h"

class Shader final
{
public:
    Shader(std::string vertexSource, std::string fragmentSource);
    ~Shader();

    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
private:
    GLuint compileShader(const char* source, GLenum shaderType);
    GLuint linkShader(GLuint vertex, GLuint fragment);
    void reportError(GLuint Id, std::string message);
private:
    unsigned int m_programID = 0;
};