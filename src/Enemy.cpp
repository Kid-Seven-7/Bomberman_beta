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

Enemy::Enemy()
{
}

Enemy::Enemy(int level, int enemyNumber, Shader shader, float pos_x, float pos_y)
{
    if (level == 1) //Level 1 Enemy model
        this->enemy_model = Model();
    if (level == 2) //Level 2 Enemy model
        this->enemy_model = Model();
    if (level == 3) //Level 3 Enemy model
        this->enemy_model = Model();

    //Enemy movement
    this->pos_x = pos_x;
    this->pos_y = pos_y;

    //Enemy shader
    this->shader = shader;
}

int     Enemy::getEnemyNumber()
{
    return (0);
}

void    Enemy::setEnemyDirection(int direction)
{

}

void    Enemy::move()
{

}

void    Enemy::drawEnemy()
{
}

Enemy::~Enemy() {}