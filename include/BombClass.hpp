/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BombClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 11:07:33 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/16 16:13:30 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BOMB_CLASS
# define BOMB_CLASS

# include "../include/model.hpp"
# include "../include/sound.hpp"

class BombClass
{
    public:
        BombClass();
        ~BombClass();

        void    putBomb(Shader shader, float pos_x, float pos_y, int currentBombModel);
        void    drawBomb(Shader shader, int currentBombModel);

    private:
        Model   bombModel_1;
        Model   bombModel_2;
        float   pos_x;
        float   pos_y;
};

# endif