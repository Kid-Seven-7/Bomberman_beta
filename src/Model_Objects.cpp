/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model_Objects.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:49:07 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/19 13:37:51 by amatshiy         ###   ########.fr       */
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
    // this->player_life = Model("bomberman_assets/player/bb8/bb8-body-to_scale1.obj");
    // this->player_head = Model("bomberman_assets/player/bb8/bb8-head-to_scale.obj");
    this->portal_door = Model("bomberman_assets/misc/portal1.obj");
    this->clock_model = Model("bomberman_assets/clock/clockInvert.obj");
    this->clock_hand_model = Model("bomberman_assets/clock/clock-arm.obj");
    this->you_win_model = Model("bomberman_assets/misc/youWinCube.obj");
    this->you_lose_model = Model("bomberman_assets/misc/youLoseCube.obj");
    this->score_model = Model("bomberman_assets/clock/holder.obj");
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

    //Resizing the bb_head model
    engine_model = glm::scale(engine_model, glm::vec3(2.0f, 2.0f, 2.0f));

    //engine_model rotation
    // engine_model = glm::rotate(engine_model, 5.02f ,glm::vec3(1.0f, 0.0f, 0.0f));
    engine_model = glm::rotate(engine_model, (float)glfwGetTime() * 6.0f  ,glm::vec3(0.0f, -1.0f, 0.0f));

    //Drawing the bb_head model
    shader.setMat4("model", engine_model);
    this->engine_model.Draw(shader);
}

//PORTAL DOOR
void    Model_Objects::PortalDoor(Shader shader, float pos_x, float pos_y)
{
    glm::mat4   portal_door = glm::mat4(1.0f);

    //Softwalls positions
    portal_door = glm::translate(portal_door, glm::vec3(-1.9f + pos_x, -1.1f, -1.9f + pos_y));

    //Resising the soft wall model
    portal_door = glm::scale(portal_door, glm::vec3(0.5f, 0.5f, 0.5f));

    portal_door = glm::rotate(portal_door, (float)glfwGetTime() * 35.0f ,glm::vec3(0.0f, 1.0f, 0.0f));

    //Drawing the soft wall model
    shader.setMat4("model", portal_door);
    this->portal_door.Draw(shader);
}

void    Model_Objects::ClockModel(Shader shader)
{
    glm::mat4   clock_ = glm::mat4(1.0f);

    //Clock positions
    clock_ = glm::translate(clock_, glm::vec3(-8.0f, 3.5f, -1.9f));

    //Resising the clock model
    clock_ = glm::scale(clock_, glm::vec3(0.5f, 0.5f, 0.5f));

    clock_ = glm::rotate(clock_ , -0.4f ,glm::vec3(1.0f, 0.0f, 0.0f));
    clock_ = glm::rotate(clock_ , 0.4f ,glm::vec3(0.0f, 1.0f, 0.0f));
    clock_ = glm::rotate(clock_, 0.05f,glm::vec3(0.0f, 0.0f, 1.0f));

    //Drawing the soft wall model
    shader.setMat4("model", clock_);
    this->clock_model.Draw(shader);
}

void    Model_Objects::ClockHand(Shader shader)
{
    glm::mat4   clock_hand_ = glm::mat4(1.0f);

    //Clock positions
    clock_hand_ = glm::translate(clock_hand_, glm::vec3(-8.0f, 3.5f, -1.9f));

    //Resising the clock model
    clock_hand_ = glm::scale(clock_hand_, glm::vec3(0.5f, 0.5f, 0.5f));

    clock_hand_ = glm::rotate(clock_hand_ , -0.4f ,glm::vec3(1.0f, 0.0f, 0.0f));
    clock_hand_ = glm::rotate(clock_hand_ , 0.4f ,glm::vec3(0.0f, 1.0f, 0.0f));
    clock_hand_ = glm::rotate(clock_hand_, -(float)glfwGetTime() / 10.0f,glm::vec3(0.0f, 0.0f, 1.0f));

    //Drawing the soft wall model
    shader.setMat4("model", clock_hand_);
    this->clock_hand_model.Draw(shader);
}

void    Model_Objects::Score(Shader shader)
{
    glm::mat4   score_ = glm::mat4(1.0f);

    //Clock positions
    score_ = glm::translate(score_, glm::vec3(8.0f, 3.5f, -1.9f));

    score_ = glm::rotate(score_ , -0.4f ,glm::vec3(1.0f, 0.0f, 0.0f));
    score_ = glm::rotate(score_ , -0.4f ,glm::vec3(0.0f, 1.0f, 0.0f));

    //Resising the clock model
    score_ = glm::scale(score_, glm::vec3(1.5f, 1.5f, 1.5f));

    //Drawing the soft wall model
    shader.setMat4("model", score_);
    this->score_model.Draw(shader);
}

void    Model_Objects::gameOverScreen(Shader shader, int model)
{
     glm::mat4   state_model = glm::mat4(1.0f);

    //Softwalls positions
    state_model = glm::translate(state_model, glm::vec3(4.5f, -2.5f, -1.9f));

    //Resising the soft wall model
    state_model = glm::scale(state_model, glm::vec3(5.0f, 5.0f, 5.0f));

    state_model = glm::rotate(state_model , 2.5f ,glm::vec3(1.0f, 0.0f, 0.0f));

    state_model = glm::rotate(state_model , (float)glfwGetTime() ,glm::vec3(0.0f, 1.0f, 0.0f));

    //Drawing the soft wall model
    shader.setMat4("model", state_model);
    if (model == 1)
        this->you_win_model.Draw(shader);
    else if (model == 2)
        this->you_lose_model.Draw(shader);
}