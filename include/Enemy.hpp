/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 13:23:46 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/19 14:25:58 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef    ENEMY_HPP
# define    ENEMY_HPP

# include "model.hpp"

# define    CHECK_UP 1
# define    CHECK_RIGHT 2
# define    CHECK_DOWN 3
# define    CHECK_LEFT 4

# define    CHECK_BOMB 4 //BOMB VALUE ON THE MAP

class   Enemy
{
    public:
        Enemy();
        Enemy(int enemyNumber, Shader shader, int level = 1);
        ~Enemy();

        void    move();
        void    enemyAI(std::vector<std::vector<int> > & map);
        int     check_if_empty(std::vector<std::vector<int> > map);

        //SETTERS AND GETTERS
        void    setEnemyDirection(int direction);
        void    setObjCoords(int obj_x, int obj_y);
        void    setPosCoords(float pos_x, float pos_y);
        int     getEnemyNumber();
        int     getObjXCoord();
        int     getObjYCoord();
        float   getXCoord();
        float   getYCoord();

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

        //Vector of possible coordinates
        std::vector<int>    p_coords;

        //Movement
        void    drawEnemy();
        int     changeDirection();

};

# endif