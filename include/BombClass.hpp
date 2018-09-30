/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BombClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 11:07:33 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/30 12:53:27 by amatshiy         ###   ########.fr       */
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

        void    putBomb(Shader shader, float pos_x, float pos_y);
        void    drawBomb(Shader shader);

    private:
        Model   bombModel;
        float   pos_x;
        float   pos_y;
};

# endif