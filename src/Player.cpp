/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:30:40 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 17:29:23 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/Player.hpp"

Player::Player()
{
    //init body ratation variables
    this->body_r_x = 0.0f;
    this->body_r_y = 0.0f;

    //init body movement variables
    this->move_x = 1.3f;
    this->move_y = 1.3f;

    //Player head init
    this->player_head = Model("bomberman_assets/player/bb8/bb8-head-to_scale.obj");
    //Player body init
    this->player_body = Model("bomberman_assets/player/bb8/bb8-body-to_scale1.obj");
}

Player::~Player() {}

//Function for head movement
void    Player::headModel(Shader shader)
{
    glm::mat4   player_head = glm::mat4(1.0f);

    //Player head movements
    player_head = glm::translate(player_head, glm::vec3(-0.5f + this->move_x, -0.25f, -0.60f + this->move_y));

    //Resizing the head model down
    player_head = glm::scale(player_head, glm::vec3(0.7f, 0.7f, 0.7f));

    //Drawing the head model
    shader.setMat4("model", player_head);
    this->player_head.Draw(shader);
}

//Function for body rotation and movement
void    Player::bodyModel(Shader shader)
{
    glm::mat4 player_body = glm::mat4(1.0f);

    //Player body movement
    player_body = glm::translate(player_body, glm::vec3(-0.5f + this->move_x, -0.95f, -0.60f + this->move_y));

    //Resizing the model body down
    player_body = glm::scale(player_body, glm::vec3(0.7f, 0.7f, 0.7f));

    //Body rotation
    player_body = glm::rotate(player_body, this->body_r_x, glm::vec3(0.0f, 0.0f, -1.0f));  //rotating the x axis
    player_body = glm::rotate(player_body, this->body_r_y, glm::vec3(-1.0f, 0.0f, 0.0f));  //rotating the y axis

    //Drawing the body model
    shader.setMat4("model", player_body);
    this->player_body.Draw(shader);
}

//To control the player's movements
void    Player::playerMovements(GLFWwindow *window, Sound &sound, Keys &keys)
{
	(void)window;
    //PLAYER MOVEMENTS
    if (keys.input() == UP)
    {
			sound.playFX(BB8_MISC);
      this->move_y -= 0.1f;
      this->body_r_y += 0.2f;
    }
    else if (keys.input() == DOWN)
    {
			sound.playFX(BB8_MISC);
      move_y += 0.1f;
      this->body_r_y -= 0.2f;
    }
    else
      this->body_r_y = 0.0f;

    if (keys.input() == RIGHT)
    {
			sound.playFX(BB8_MISC);
      this->move_x += 0.1f;
      this->body_r_x += 0.2f;
    }
    else if (keys.input() == LEFT)
    {
			sound.playFX(BB8_MISC);
      move_x -= 0.1f;
      this->body_r_x -= 0.2f;
    }
    else
      this->body_r_x = 0.0f;
}

float   Player::getXcoord() { return (move_x); }

float   Player::getYcoord() { return (move_y); }
