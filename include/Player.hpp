/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:23:06 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/29 15:22:45 by amatshiy         ###   ########.fr       */
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

//Movement Directions
# define MOVE_UP    1
# define MOVE_DOWN  2
# define MOVE_LEFT  3
# define MOVE_RIGHT 4

class Player
{
    public:
        Player();
        ~Player();


        //Body rotation and movement
        void    bodyModel(Shader shader);
        void    headModel(Shader shader);
        int    playerMovements(GLFWwindow *window, Sound &sound, Keys &keys, std::vector<std::vector<int> >  mapOfObjects);
        float   getXcoord();
        float   getYcoord();
        std::vector<std::vector<int> > getMapUpdate();
        std::vector<int>    getPrevPlayer();
        std::vector<int>    getNewPlayerPos();


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

        //Checking if movement is possible
        std::vector<int>    playerPos;
        std::vector<int>    NewPlayerPos;
        std::vector<std::vector<int> > mapOfObjectsUpdate;
        void     getPlayerPos(std::vector<std::vector<int> >  mapOfObjects); //Search for the player
        int     checkNexPos(int direction, std::vector<std::vector<int> >  mapOfObjects); //Checking position next to the player
};

# endif
