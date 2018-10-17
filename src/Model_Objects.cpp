/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model_Objects.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:49:07 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/17 11:39:27 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/Model_Objects.hpp"

Model_Objects::Model_Objects()
{
    //Model variables init
    this->soft_wall = Model("bomberman_assets/misc/smooth-cube-misc1.obj");
    this->hard_wall = Model("bomberman_assets/misc/smooth-cube-misc.obj");
    this->universe_model = Model("bomberman_assets/universe/mulan-universe.obj");
    this->engine_model = Model("bomberman_assets/timeship/timeship.obj");
    this->base_model = Model("bomberman_assets/timeship/BASE.obj");
    this->player_life = Model("bomberman_assets/player/bb8/bb8-body-to_scale1.obj");
    this->player_head = Model("bomberman_assets/player/bb8/bb8-head-to_scale.obj");
}

Model_Objects::~Model_Objects() {}

void    Model_Objects::soft_wall_func(Shader shader, float pos_x, float pos_y)
{
    glm::mat4   soft_wall_model = glm::mat4(1.0f);

    //Softwalls positions
    soft_wall_model = glm::translate(soft_wall_model, glm::vec3(-1.9 + pos_x, -1.1, -1.9 + pos_y));

    //Resising the soft wall model
    soft_wall_model = glm::scale(soft_wall_model, glm::vec3(0.7f, 0.7f, 0.7f));

    //Drawing the soft wall model
    shader.setMat4("model", soft_wall_model);
    this->soft_wall.Draw(shader);
}

void    Model_Objects::hard_wall_func(Shader shader, float pos_x, float pos_y)
{
     glm::mat4   hard_wall_model = glm::mat4(1.0f);

    //Softwalls positions
    hard_wall_model = glm::translate(hard_wall_model, glm::vec3(-1.9 + pos_x, -1.1, -1.9 + pos_y));

    //Resising the soft wall model
    hard_wall_model = glm::scale(hard_wall_model, glm::vec3(0.7f, 0.7f, 0.7f));

    //Drawing the soft wall model
    shader.setMat4("model", hard_wall_model);
    this->hard_wall.Draw(shader);
}

void    Model_Objects::player_life_func(Shader shader, float pos_x, float pos_y)
{
    glm::mat4   player_life_model = glm::mat4(1.0f);

    //Softwalls positions
    player_life_model = glm::translate(player_life_model, glm::vec3(-1.9 + pos_x, -1.1, -1.9 + pos_y));

    //Resising the soft wall model
    player_life_model = glm::scale(player_life_model, glm::vec3(0.7f, 0.7f, 0.7f));

    //Drawing the soft wall model
    shader.setMat4("model", player_life_model);
    this->player_life.Draw(shader);
}

void    Model_Objects::headModel(Shader shader, float pos_x, float pos_y)
{
    glm::mat4   player_head = glm::mat4(1.0f);

    //Player head movements
    player_head = glm::translate(player_head, glm::vec3(-1.9 + pos_x, -1.1, -1.9 + pos_y));

    //Resizing the head model down
    player_head = glm::scale(player_head, glm::vec3(0.7f, 0.7f, 0.7f));

    //Drawing the head model
    shader.setMat4("model", player_head);
    this->player_head.Draw(shader);
}

void    Model_Objects::universe_func(Shader shader)
{
     glm::mat4   universe = glm::mat4(1.0f);

    //Softwalls positions
    universe = glm::translate(universe, glm::vec3(1.0f, -2.5f, -1.9f));

    //Resising the soft wall model
    universe = glm::scale(universe, glm::vec3(0.4f, 0.4f, 0.4f));

    universe = glm::rotate(universe, (float)glfwGetTime() / 15.0f ,glm::vec3(0.0f, 1.0f, 0.0f));

    //Drawing the soft wall model
    shader.setMat4("model", universe);
    this->universe_model.Draw(shader);
}

void    Model_Objects::base_func(Shader shader)
{
     glm::mat4   base = glm::mat4(1.0f);

    //Softwalls positions
    base = glm::translate(base, glm::vec3(4.5f, -8.5f, 3.5f));

    //Resising the soft wall model
    base = glm::scale(base, glm::vec3(4.5f, 4.5f, 4.5f));

    // base = glm::rotate(base, (float)glfwGetTime() / 15.0f ,glm::vec3(0.0f, 1.0f, 0.0f));

    //Drawing the soft wall model
    shader.setMat4("model", base);
    this->base_model.Draw(shader);
}

void    Model_Objects::Engine(Shader shader, float pos_x, float pos_y)
{
    glm::mat4   engine_model = glm::mat4(1.0f);

    //bb_head positions
    engine_model = glm::translate(engine_model, glm::vec3(pos_x, 4.0f, pos_y));

    //Resising the bb_head model
    engine_model = glm::scale(engine_model, glm::vec3(2.0f, 2.0f, 2.0f));

    //engine_model rotation
    // engine_model = glm::rotate(engine_model, 5.02f ,glm::vec3(1.0f, 0.0f, 0.0f));
    engine_model = glm::rotate(engine_model, (float)glfwGetTime() * 6.0f  ,glm::vec3(0.0f, -1.0f, 0.0f));

    //Drawing the bb_head model
    shader.setMat4("model", engine_model);
    this->engine_model.Draw(shader);
}
