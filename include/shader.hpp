    /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:30:12 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/24 15:53:29 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __SHADER_HPP__
# define __SHADER_HPP__

# include <glad/glad.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

class Shader
{
    public:
        unsigned int ID; //program ID
        Shader();
        ~Shader();
        Shader(const char *vertexPath, const char *fragmentPath);

        void    use();
        void    compileShader(unsigned int &shaderID, int type, const char *shaderCode);
        void    setBool(const std::string &name, bool value);
        void    setInt(const std::string &name, int value);
        void    setFloat(const std::string &name, float value);
        int     getLocation(std::string var);
        void    setVec2(const std::string &name, const glm::vec2 &value) const;
        void    setVec2(const std::string &name, float x, float y) const;
        void    setVec3(const std::string &name, const glm::vec3 &value) const;
        void    setVec3(const std::string &name, float x, float y, float z) const;
        void    setVec4(const std::string &name, const glm::vec4 &value) const;
        void    setVec4(const std::string &name, float x, float y, float z, float w);
        void    setMat2(const std::string &name, const glm::mat2 &mat) const;
        void    setMat3(const std::string &name, const glm::mat3 &mat) const;
        void    setMat4(const std::string &name, const glm::mat4 &mat) const;
};

# endif
