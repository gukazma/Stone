#include "Function/Render/Implement/OpenGL/OpenGLShader.h"
#include "Core/Base/macro.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
namespace Stone
{
    int OpenGLShader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                LOG_ERROR("{0} Shader complie error, error code: {1}", type, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                LOG_ERROR("{0} Shader complie error, error code: {1}", type, infoLog);
            }
        }
        return success;
    }

    void OpenGLShader::bind()
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::unbind()
    {
        glUseProgram(0);
    }

    OpenGLShader::OpenGLShader(const std::string& name)
        : m_RendererID(glCreateProgram()), m_Name(name)
    {
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteShader(m_RendererID);
    }

    void OpenGLShader::link(const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize)
    {
        GLuint svert = glCreateShader(GL_VERTEX_SHADER);
        glShaderBinary(1, &svert, GL_SHADER_BINARY_FORMAT_SPIR_V, vshader, vsiz);
        glSpecializeShader(svert, "main", 0, nullptr, nullptr);
        ASSERT(checkCompileErrors(svert, "VERTEX"), "VERXTEX shader error");
        glAttachShader(m_RendererID, svert);

        GLuint sfrag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderBinary(1, &sfrag, GL_SHADER_BINARY_FORMAT_SPIR_V, fshader, fsize);
        glSpecializeShader(sfrag, "main", 0, nullptr, nullptr);
        glAttachShader(m_RendererID, sfrag);
        ASSERT(checkCompileErrors(sfrag, "FRAGMENT"), "FRAGMENT shader error");

        glLinkProgram(m_RendererID);
        ASSERT(checkCompileErrors(m_RendererID, "PROGRAM"), "Shader Link error");
        glDeleteShader(svert);
        glDeleteShader(sfrag);
    }

    void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) const
    {
        int flag = glGetUniformLocation(m_RendererID, name.c_str());
        if (flag != -1)
        {
            glUniformMatrix4fv(flag, 1, GL_FALSE, glm::value_ptr(value));
        }


    }

    void OpenGLShader::setInt(const std::string& name, uint32_t value) const
    {
        int flag = glGetUniformLocation(m_RendererID, name.c_str());
        if (flag != -1)
        {
            glUniform1i(flag, value);
        }
    }
}
