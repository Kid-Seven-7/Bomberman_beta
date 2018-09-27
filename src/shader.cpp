/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:55:03 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 08:38:00 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shader.hpp"

Shader::Shader()
{
}

Shader::~Shader() {}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    //store result from file
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        //reading to streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //closing files
        vShaderFile.close();
        fShaderFile.close();

        //convert stream into a string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    //compiling shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    this->compileShader(vertex, GL_VERTEX_SHADER, vShaderCode);
    this->compileShader(fragment, GL_FRAGMENT_SHADER, fShaderCode);

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(this->ID, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::SHADER::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    //deleting shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void    Shader::use()
{
    glUseProgram(ID);
}

void    Shader::compileShader(unsigned int &shaderID, int type, const char *shaderCode)
{
    int success;
    char infoLog[512];

    shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        if (type == GL_VERTEX_SHADER)
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        else
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
    }
}

void    Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), int(value));
}

void    Shader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void    Shader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

int     Shader::getLocation(std::string var)
{
    return glGetUniformLocation(this->ID, var.c_str());
}

//Last shader update
void    Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void    Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void    Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void    Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void    Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void    Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void    Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void    Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void    Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}