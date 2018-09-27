/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 11:10:13 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 08:44:22 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MODEL_HPP
# define MODEL_HPP

# include <glad/glad.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "../Image_Loader/image_loader.hpp"

//assimp headers
# include <assimp/Importer.hpp>
# include <assimp/scene.h>
# include <assimp/postprocess.h>
# include "../Image_Loader/stb_image.h"

# include "mesh.hpp"
# include "shader.hpp"

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <map>
# include <vector>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class   Model
{
    public:
            /* Model Data */
            Model();
            ~Model();

            std::vector<Texture>    textures_loaded;
            std::vector<Mesh>   meshes;
            std::string     directory;
            bool    gammaCorrection;

            /* Functions */
            void        setModel(std::string const &path, bool gamma = false);
            Model(std::string const &path, bool gamma = false);
            void    Draw(Shader shader);

    private:
            /* Functions */
            void    loadModel(std::string const path);
            void    processNode(aiNode *node, const aiScene *scene);
            Mesh    processMesh(aiMesh *mesh, const aiScene *scene);
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string);
};

# endif