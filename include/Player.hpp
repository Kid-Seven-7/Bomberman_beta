/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:23:06 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 08:46:38 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PLAYER
# define PLAYER

# include "../include/model.hpp"
# include "../include/sound.hpp"
# include "../include/keys.hpp"

//Key returns
# define 			UP 100
# define 			DOWN 101
# define 			LEFT 102
# define 			RIGHT 103
# define 			ACTION 104
# define 			ENTER 105
# define 			NEXT 106
# define 			PREV 107
# define 			EXIT 108

class Player
{
    public:
        Player();
        ~Player();


        //Body rotation and movement
        void    bodyModel(Shader shader);
        void    headModel(Shader shader);
        void    playerMovements(GLFWwindow *window, Sound &sound, Keys &keys);
        float   getXcoord();
        float   getYcoord();

    private:
        //Player models
        Model   player_head;
        Model   player_body;

        //Body rotation
        float   body_r_x;
        float   body_r_y;

        //Player movements
        float   move_x;
        float   move_y;
};

# endif
