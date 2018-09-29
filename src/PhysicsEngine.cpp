/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhysicsEngine.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 11:03:13 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 12:09:24 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/PhysicsEngine.hpp"

PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {}

void    PhysicsEngine::getPlayerObject(Player player)
{
    //Initializing player object
    this->p_object = player;
}

void    PhysicsEngine::getUpdatedArray(std::vector<std::vector<std::vector<float> > > map_of_coords)
{
    //Updating the map containing coordinates of objects in space
    this->updateArray.clear();
    this->updateArray = map_of_coords;
}

void    PhysicsEngine::getUpdatedObjectsArray(std::vector<std::vector<int> > map_of_objects)
{
    //Updating the Map containing objects
    this->map_of_objects_array.clear();
    this->map_of_objects_array = map_of_objects;
}

void    PhysicsEngine::testClass()
{
    //Map of objects loop
    for (size_t i = 0; i < this->map_of_objects_array.size(); i++)
    {
        for (size_t j = 0; j < this->map_of_objects_array[i].size(); j++)
        {
            std::cout << this->map_of_objects_array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //Map of coordinates loop
    std::cout << std::endl;
    for (size_t i = 0; i < this->updateArray[0].size(); i++)
    {
        for (size_t j = 0; j < this->updateArray[i].size(); j++)
        {
            for (size_t k = 0; k < this->updateArray[i][j].size(); k++)
            {
                std::cout << this->updateArray[i][j][k] << " ";
            }
        }
        std::cout << std::endl;
    }
}
