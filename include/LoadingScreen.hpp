/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadingScreen.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 21:43:58 by amatshiy          #+#    #+#             */
/*   Updated: 2018/11/15 09:24:10 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LOADING_SCREEN
# define LOADING_SCREEN

# include "HeaderHandler.hpp"
# include "bomberman.hpp"

class LoadingScreen
{
    public:
        LoadingScreen();
        ~LoadingScreen();

        void    LoadGame(GLFWwindow  *window, Sound &sound, Keys &keys, int level, int lives);
};

# endif
