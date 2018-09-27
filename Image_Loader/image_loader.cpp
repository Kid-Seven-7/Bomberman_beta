/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 09:24:44 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/19 12:37:57 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "image_loader.hpp"
# define STB_IMAGE_IMPLEMENTATION
# include "stb_image.h"

ImageLoader::ImageLoader() {}

ImageLoader::ImageLoader(std::string file_path, int &width, int &height, int &nrChannels)
{
    //checking if value for file_path is not empty
    if (file_path.empty() && file_path.length() < 1)
    {
        std::cout << "\033[1;31mError\033[0m: No path was passed." << std::endl;
        exit(1);
    }

    //casting file_path to a const char * for stbi_load()
    const char * path = static_cast<const char *>(file_path.c_str());

    //initializing ImageData using the image given
    stbi_set_flip_vertically_on_load(true);
    this->ImageData = stbi_load(path, &width, &height, &nrChannels, 0);
}

ImageLoader::~ImageLoader() {}

unsigned char * ImageLoader::getImageData()
{
    //return image data initialized in the constructor
    return (this->ImageData);
}

void    ImageLoader::freeImageData()
{
    //frees image data
    stbi_image_free(this->ImageData);
}