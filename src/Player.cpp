/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:30:40 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/16 15:07:45 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/Player.hpp"

Player::Player()
{
    //init body ratation variables
    this->body_r_x = 0.0f;
    this->body_r_y = 0.0f;

    //init body movement variables
    this->move_x = 0.0f;
    this->move_y = 0.0f;

    //Player head init
    this->player_head = Model("bomberman_assets/player/bb8/bb8-head-to_scale.obj");
    //Player body init
    this->player_body = Model("bomberman_assets/player/bb8/bb8-body-to_scale1.obj");
}

Player::~Player() 
{
  this->move_x = 0.0f;
  this->move_y = 0.0f;
}

//Function for head movement
void    Player::headModel(Shader shader)
{
    glm::mat4   player_head = glm::mat4(1.0f);

    //Player head movements
    player_head = glm::translate(player_head, glm::vec3(-0.5f + this->move_x, -0.85f, -0.60f + this->move_y));

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
int    Player::playerMovements(GLFWwindow *window, Sound &sound, Keys &keys, std::vector<std::vector<int> >  mapOfObjects, int& player_direction)
{
	(void)window;
  (void)sound;
  (void)mapOfObjects;
    //PLAYER MOVEMENTS
    if (keys.input() == UP)
    {
			// sound.playFX(BB8_MISC);
      if (this->checkNexPos(MOVE_UP, mapOfObjects) == 1)
      {
        // std::cout << "Return is: " << !(this->checkNexPos(MOVE_UP, mapOfObjects) == -1) << std::endl;
        this->move_y -= 0.1f;
        this->body_r_y += 0.2f;
        player_direction = MOVE_UP;
        return (1);
      }
      else
        this->body_r_y += 0.2f;
    }
    else if (keys.input() == DOWN)
    {
			// sound.playFX(BB8_MISC);
      if (this->checkNexPos(MOVE_DOWN, mapOfObjects) == 1)
      {
        move_y += 0.1f;
        this->body_r_y -= 0.2f;
        player_direction = MOVE_DOWN;
        return (1);
      }
      else
        this->body_r_y -= 0.2f;
    }
    else if (keys.input() == RIGHT)
    {
			// sound.playFX(BB8_MISC);
      // std::cout << "Key INPUT = RIGHT" << std::endl;
      if (this->checkNexPos(MOVE_RIGHT, mapOfObjects) == 1)
      {
        // std::cout << "Return is: " << !(this->checkNexPos(MOVE_RIGHT, mapOfObjects) == -1) << std::endl;
        this->move_x += 0.1f;
        this->body_r_x += 0.2f;
        player_direction = MOVE_RIGHT;
        return (1);
      }
      else
        this->body_r_x += 0.2f;
    }
    else if (keys.input() == LEFT)
    {
			// sound.playFX(BB8_MISC);
      if (this->checkNexPos(MOVE_LEFT, mapOfObjects) == 1)
      {
        this->move_x -= 0.1f;
        this->body_r_x -= 0.2f;
        player_direction = MOVE_LEFT;
        return (1);
      }
      else
        this->body_r_x -= 0.2f;
    }
    else
    {
      this->body_r_x = 0.0f; //Reseting body rotation
      this->body_r_y = 0.0f;
    }
    return (-1);
}

//Getting current position of the player
void  Player::getPlayerPos(std::vector<std::vector<int> >  mapOfObjects)
{
  // std::cout << "mapOfObjects: 1: " << mapOfObjects.size() << std::endl;    
  int player_found = 0;
  for (unsigned int i = 0; i < mapOfObjects.size(); i++)
  {
    for (unsigned int j = 0; j < mapOfObjects[i].size(); j++)
    {
      // std::cout << "mapOfObjects: 2: " << mapOfObjects[i].size() << std::endl;    
      if (mapOfObjects[i][j] == 3)
      {
        player_found = 1;
        // std::cout << "Player Pos Value: " << mapOfObjects[i][j] << std::endl;
        // std::cout << "Player X Pos: " << j << std::endl;
        // std::cout << "Player Y Pos: " << i << std::endl;
        this->playerPos.clear();
        this->playerPos.push_back(j);
        this->playerPos.push_back(i);
        break;
      }
    }
    if (player_found == 1)
      break;
  }
}

int     Player::checkNexPos(int direction, std::vector<std::vector<int> >  mapOfObjects)
{
  int x_player_pos = 0;
  int y_player_pos = 0;
 
  if (direction == MOVE_UP)
  {
    this->getPlayerPos(mapOfObjects);
    x_player_pos = this->playerPos[0];
    y_player_pos = this->playerPos[1];


    if ((mapOfObjects[y_player_pos - 1][x_player_pos] != 1) &&
      (mapOfObjects[y_player_pos - 1][x_player_pos] != 2) &&
      (mapOfObjects[y_player_pos - 1][x_player_pos] != 4))
    {
      // std::cout << "Next Pos: " << mapOfObjects[y_player_pos - 1][x_player_pos] << std::endl;
      //Storing new player position
      this->NewPlayerPos.clear();
      this->NewPlayerPos.push_back(x_player_pos);
      this->NewPlayerPos.push_back(y_player_pos - 1);

      return (1);
    }
  }
  if (direction == MOVE_DOWN)
  {
    this->getPlayerPos(mapOfObjects);
    x_player_pos = this->playerPos[0];
    y_player_pos = this->playerPos[1];


    if ((mapOfObjects[y_player_pos + 1][x_player_pos] != 1) &&
      (mapOfObjects[y_player_pos + 1][x_player_pos] != 2) &&
      (mapOfObjects[y_player_pos - 1][x_player_pos] != 4))
    {
      // std::cout << "Next Pos: " << mapOfObjects[y_player_pos - 1][x_player_pos] << std::endl;
      //Storing new player position
      this->NewPlayerPos.clear();
      this->NewPlayerPos.push_back(x_player_pos);
      this->NewPlayerPos.push_back(y_player_pos + 1);

      return (1);
    }
  }
  if (direction == MOVE_LEFT)
  {
    // std::cout << "Moving to the right" << std::endl;
    this->getPlayerPos(mapOfObjects);
    x_player_pos = this->playerPos[0];
    y_player_pos = this->playerPos[1];

    // std::cout << "X_POS_RIGHT: " << this->playerPos[0] << std::endl;
    // std::cout << "Y_POS_RIGHT: " << this->playerPos[1] << std::endl;
    if ((mapOfObjects[y_player_pos][x_player_pos - 1] != 1) &&
      (mapOfObjects[y_player_pos][x_player_pos - 1] != 2) &&
      (mapOfObjects[y_player_pos - 1][x_player_pos] != 4))
    {
      // std::cout << "Next Pos: " << mapOfObjects[y_player_pos][x_player_pos + 1] << std::endl;
      //Storing new player position
      this->NewPlayerPos.clear();
      this->NewPlayerPos.push_back(x_player_pos - 1);
      this->NewPlayerPos.push_back(y_player_pos);

      return (1);
    }
  }
  if (direction == MOVE_RIGHT)
  {
    // std::cout << "Moving to the right" << std::endl;
    this->getPlayerPos(mapOfObjects);
    x_player_pos = this->playerPos[0];
    y_player_pos = this->playerPos[1];

    // std::cout << "X_POS_RIGHT: " << this->playerPos[0] << std::endl;
    // std::cout << "Y_POS_RIGHT: " << this->playerPos[1] << std::endl;
    if ((mapOfObjects[y_player_pos][x_player_pos + 1] != 1) &&
      (mapOfObjects[y_player_pos][x_player_pos + 1] != 2) &&
      (mapOfObjects[y_player_pos - 1][x_player_pos] != 4))
    {
      // std::cout << "Next Pos: " << mapOfObjects[y_player_pos][x_player_pos + 1] << std::endl;
      //Storing new player position
      this->NewPlayerPos.clear();
      this->NewPlayerPos.push_back(x_player_pos + 1);
      this->NewPlayerPos.push_back(y_player_pos);

      return (1);
    }
  }
  return (-1);
}

float   Player::getXcoord() { return (move_x + 1.3f); }

float   Player::getYcoord() { return (move_y + 1.3f); }

std::vector<std::vector<int> > Player::getMapUpdate()
{
  return (this->mapOfObjectsUpdate);
}

std::vector<int>  Player::getNewPlayerPos()
{
  return (this->NewPlayerPos);
}

std::vector<int>  Player::getPrevPlayer()
{
  return (this->playerPos);
}