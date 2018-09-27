/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model_Objects.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:49:16 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 18:34:33 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MODEL_OBJECTS
# define MODEL_OBJECTS

# include "model.hpp"

class Model_Objects
{
    public:
        Model_Objects();
        ~Model_Objects();

        void    soft_wall_func(Shader shader, float pos_x, float pos_y);
        void    hard_wall_func(Shader shader, float pos_x, float pos_y);
        void    universe_func(Shader shader);
        void    base_func(Shader shader);
        void    Engine(Shader shader, float pos_x, float pos_y);


    private:
        //Model variables
        Model   soft_wall;
        Model   hard_wall;
        Model   universe_model;
        Model   engine_model;
        Model   base_model;
};

# endif