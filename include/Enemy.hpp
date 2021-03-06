/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 13:23:46 by amatshiy          #+#    #+#             */
/*   Updated: 2018/11/03 00:29:53 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef    ENEMY_HPP
# define    ENEMY_HPP

# include "model.hpp"
# include <time.h>
# include <unistd.h>
// # include <fenv.h>
// # pragma STDC FENV_ACCESS ON

# define    CHECK_UP 1
# define    CHECK_RIGHT 2
# define    CHECK_DOWN 3
# define    CHECK_LEFT 4

# define    DIRECTION_UP    2.5f
# define    DIRECTION_RIGHT 0.9f
# define    DIRECTION_DOWN  -0.65f
# define    DIRECTION_LEFT  -2.3F

# define    CHECK_BOMB 4 //BOMB VALUE ON THE MAP

class   Enemy
{
    public:
        Enemy();
        Enemy(int enemyNumber, Shader shader, int level = 1);
        ~Enemy();

        void    move();
        void    enemyAI(std::vector<std::vector<int> > & map);
        void    check_possible_directions(std::vector<std::vector<int> > map);
        int     choosePath();
        bool    checkDirection(std::vector<std::vector<int> > & map);

        //SETTERS AND GETTERS
        void    setEnemyDirection(int direction);
        void    setObjCoords(int obj_x, int obj_y);
        void    setPosCoords(float pos_x, float pos_y);
        void    drawEnemy();
        void    updateEnemyLocation(std::vector<std::vector<int> > & map);
        

        int     getEnemyNumber();
        int     getObjXCoord();
        int     getObjYCoord();
        float   getXCoord();
        float   getYCoord();
        bool    playerBeDead();
        void    setPlayerState(bool state);


    private:
        Model   enemy_model;
        Shader  shader;

        int     enemyNumber; //USED TO REFERENCE THIS ENEMY
                             //USED TO CHECK FOR THIS ENEMY ON THE MAP
        int     direction;   //DIRECTION THE ENEMY IS GOING

        //Enemy map_of_objs position
        int     obj_pos_x;
        int     obj_pos_y;

        //Enemy movement positions
        float   pos_x;
        float   pos_y;
        // float   speed;
        std::vector<int>    possible_directions;

        //NEXT POINT IN THE MAP
        int     moveCounter;
        int     nextMoveCounter;

        //Vector of possible coordinates
        std::vector<int>    p_coords;

        // //PREV COORDINATES

        //UPDATE LOCATION
        bool    updateLoc;
        bool    animeLoc;
        bool    changeDirection;
        bool    playerDead;
};

# endif