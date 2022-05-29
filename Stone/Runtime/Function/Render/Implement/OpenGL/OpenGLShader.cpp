#include "Function/Render/Implement/OpenGL/OpenGLShader.h"
#include "Core/Base/macro.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
namespace Stone
{
    GLenum getGLShaderType(Shader::ShaderType type)
    {
        switch (type)
        {
        case Stone::Shader::ShaderType::Vertex_Shader:
            return GL_VERTEX_SHADER;
        case Stone::Shader::ShaderType::Geometry_Shader:
            return GL_GEOMETRY_SHADER;
        case Stone::Shader::ShaderType::Fragment_Shader:
            return GL_FRAGMENT_SHADER;
        default:
            break;
        }
    }

    std::string getGLShaderTypeString(Shader::ShaderType type)
    {
        switch (type)
        {
        case Stone::Shader::ShaderType::Vertex_Shader:
            return "VERTEX";
        case Stone::Shader::ShaderType::Geometry_Shader:
            return "GEOMETRY";
        case Stone::Shader::ShaderType::Fragment_Shader:
            return "FRAGMENT";
        default:
            break;
        }
    }
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

    uint32_t OpenGLShader::create(const uint32_t* shaderSource, size_t shadersize, ShaderType shaderType)
    {
        GLuint shaderid = glCreateShader(getGLShaderType(shaderType));
        glShaderBinary(1, &shaderid, GL_SHADER_BINARY_FORMAT_SPIR_V, shaderSource, shadersize);
        glSpecializeShader(shaderid, "main", 0, nullptr, nullptr);
        std::string typestring = getGLShaderTypeString(shaderType);
        ASSERT(checkCompileErrors(shaderid, typestring),typestring + " shader error");
        return shaderid;
    }

    void OpenGLShader::deleteShader(uint32_t shaderid)
    {
        glDeleteShader(shaderid);
    }

    void OpenGLShader::attach(uint32_t shader)
    {
        glAttachShader(m_RendererID, shader);
    }

    void OpenGLShader::link()
    {
        glLinkProgram(m_RendererID);
        ASSERT(checkCompileErrors(m_RendererID, "PROGRAM"), "Shader Link error");
    }

    void OpenGLShader::link(const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize, const uint32_t* gsshader, size_t gssize)
    {
        GLuint svert = create(vshader, vsiz, Shader::ShaderType::Vertex_Shader);
        
        attach(svert);

        GLuint sfrag = create(fshader, fsize, Shader::ShaderType::Fragment_Shader);

        attach(sfrag);
        GLuint sgeom;
        if (gsshader!=nullptr)
        {
            sgeom = create(gsshader, gssize, Shader::ShaderType::Geometry_Shader);
            attach(sgeom);
        }

        link();
        deleteShader(svert);
        deleteShader(sfrag);
        if (gsshader != nullptr)
        {
            deleteShader(sgeom);
        }
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
