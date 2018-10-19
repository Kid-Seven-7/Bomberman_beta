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

class   Enemy
{
    public:
        Enemy();
        Enemy(int level = 1, int enemyNumber, Shader shader);
        ~Enemy();

    private:
        Model   enemy_model;
        Shader  shader;
        int     enemyNumber;
        int     direction;

        //Enemy movement positions
        float   pos_x;
        float   pos_y;

        //Movement
        int     getEnemyNumber();
        void    setEnemyDirection(int direction);

        void    move();
        int     changeDirection();
        void    drawEnemy();
};

# endif