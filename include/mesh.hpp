/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:48:12 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/22 15:54:10 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MESH_HPP
# define MESH_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include "shader.hpp"

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <vector>

struct Vertex
{
    //position
    glm::vec3   Position;
    //normal
    glm::vec3   Normal;
    //texCoords
    glm::vec2   TexCoords;
    //tangent
    glm::vec3   Tangent;
    //bitangent
    glm::vec3   Bitangent;
};

struct  Texture
{
    unsigned int    id;
    std::string     type;
    std::string     path;
};

class   Mesh
{
    public:
            /*Mesh Data*/
            std::vector<Vertex>     vertices;
            std::vector<unsigned int>   indices;
            std::vector<Texture>    textures;
            unsigned int VAO;

            /* Functions */
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
            void    Draw(Shader shader);

    private:
            /* Render Data */
            unsigned int VBO, EBO;

            /* Functions */
            void    setupMesh();
};


# endif