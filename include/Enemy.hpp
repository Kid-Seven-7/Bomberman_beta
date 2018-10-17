/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 13:23:46 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/17 13:27:53 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef    ENEMY_HPP
# define    ENEMY_HPP

class   Enemy
{
    public:
        Enemy();
        ~Enemy();

    private:
        void    move();
};

# endif