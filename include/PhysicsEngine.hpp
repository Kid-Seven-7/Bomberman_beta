/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhysicsEngine.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 11:02:17 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 11:36:47 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHYSICS_ENGINE
# define PHYSICS_ENGINE

# include "../include/HeaderHandler.hpp"

class PhysicsEngine
{
    public:
        //
        PhysicsEngine();
        ~PhysicsEngine();

        //Getting update coordinates
        void    getPlayerObject(Player player);
        void    getUpdatedArray(std::vector<std::vector<std::vector<float> > > map_of_coords);
        void    getUpdatedObjectsArray(std::vector<std::vector<int> > map_of_objects);
        void    testClass();

    private:
        //Variables to store updated coordinates
        std::vector<std::vector<std::vector<float> > > updateArray;
        std::vector<std::vector<int> > map_of_objects_array;
        Player p_object;
};

# endif