/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:09:02 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/19 14:26:09 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/Enemy.hpp"

Enemy::Enemy() {}

Enemy::Enemy(int enemyNumber, Shader shader, int level)
{
    //ENEMIES CHANGE WITH LEVELS

    if (level == 1) //Level 1 Enemy model
        this->enemy_model = Model("bomberman_assets/enemies/ball driod1.obj");
    if (level == 2) //Level 2 Enemy model
        this->enemy_model = Model("bomberman_assets/enemies/drone.obj");
    if (level == 3) //Level 3 Enemy model
        this->enemy_model = Model("bomberman_assets/enemies/og-driod.obj");

    //Enemy movement
    // this->pos_x = pos_x;
    // this->pos_y = pos_y;

    this->enemyNumber = enemyNumber;
    //Enemy shader
    this->shader = shader;
}

void    Enemy::setObjCoords(int obj_x, int obj_y)
{
    //SETTING THE OBJ COORDS
    this->obj_pos_x = obj_x;
    this->obj_pos_y = obj_y;
}

void    Enemy::setPosCoords(float pos_x, float pos_y)
{
    //SETTING THE POSITION COORDS
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

int     Enemy::getEnemyNumber()
{
    return (enemyNumber);
}

void    Enemy::setEnemyDirection(int direction)
{
    this->direction = direction;
}

void    Enemy::move()
{

}

void    Enemy::drawEnemy()
{
}

Enemy::~Enemy() {}

void    Enemy::enemyAI(std::vector<std::vector<int> > & map)
{
    (void)map;
}