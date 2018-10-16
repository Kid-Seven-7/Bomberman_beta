/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BombClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 11:13:33 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/16 16:15:27 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/BombClass.hpp"

BombClass::BombClass() 
{
    //Bomb coordinates
    this->pos_x = 0.0f;
    this->pos_y = 0.0f;

    //Init Bomb Model
    this->bombModel_1 = Model("bomberman_assets/misc/power_up-concept-core.obj");
    this->bombModel_2 = Model("bomberman_assets/misc/power_up-concept-mid_shell.obj");

}

BombClass::~BombClass() {}

void    BombClass::putBomb(Shader shader, float pos_x, float pos_y, int currentBombModel)
{
    //Init Bomb coordinates
    this->pos_x = pos_x;
    this->pos_y = pos_y;

    //Drawing the bomb object
    this->drawBomb(shader, currentBombModel);
}

void    BombClass::drawBomb(Shader shader, int currentBombModel)
{
    glm::mat4   bomb_model = glm::mat4(1.0f);

    //Bomb position
    bomb_model = glm::translate(bomb_model, glm::vec3(this->pos_x - 1.9f, -0.95f, this->pos_y - 2.0f));

    //Resizing bomb model
    bomb_model = glm::scale(bomb_model, glm::vec3(0.15f, 0.15f, 0.15f));

    //Rotating bomb model
    bomb_model = glm::rotate(bomb_model, (float)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    // bomb_model = glm::rotate(bomb_model, );

    //Drawing the bomb model
    shader.setMat4("model", bomb_model);
    if (currentBombModel == 1)
        this->bombModel_1.Draw(shader);
    if (currentBombModel == 2)
        this->bombModel_2.Draw(shader);
}