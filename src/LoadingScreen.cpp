/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadingScreen.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 21:50:09 by amatshiy          #+#    #+#             */
/*   Updated: 2018/11/02 23:23:35 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/LoadingScreen.hpp"

LoadingScreen::LoadingScreen() {}

LoadingScreen::~LoadingScreen() {}

void    LoadingScreen::LoadGame(GLFWwindow  *window, Sound &sound, Keys &keys, int level)
{
    GraphicsEngine e_engine = GraphicsEngine(window);

    e_engine.MainControl(sound, keys, level);
}