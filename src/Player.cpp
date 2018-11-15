/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:30:40 by amatshiy          #+#    #+#             */
/*   Updated: 2018/11/14 18:24:25 by amatshiy         ###   ########.fr       */
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
    // this->player_head = Model("bomberman_assets/player/bb8/bb8-head-to_scale.obj");
    //Player body init
    this->player_body = Model("bomberman_assets/player/bb8/bb8-body-to_scale1.obj");
    this->currentDirection = 0;
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
  (void)mapOfObjects;
    //PLAYER MOVEMENTS
    if (keys.input() == UP)
    {
			sound.playFX(BB8_MISC);
      if (this->checkNexPos(MOVE_UP, mapOfObjects) == 1)
      {
        this->move_y -= 0.2f;
        this->body_r_y += 0.3f;
        player_direction = MOVE_UP;
        this->currentDirection = MOVE_UP;
        return (1);
      }
      else
      {
        this->body_r_y += 0.3f;
      }
    }
    else if (keys.input() == DOWN)
    {
			// sound.playFX(BB8_MISC);
      if (this->checkNexPos(MOVE_DOWN, mapOfObjects) == 1)
      {
        move_y += 0.2f;
        this->body_r_y -= 0.3f;
        player_direction = MOVE_DOWN;
        this->currentDirection = MOVE_DOWN;
        return (1);
      }
      else
        this->body_r_y -= 0.3f;
    }
    else if (keys.input() == RIGHT)
    {
      if (this->checkNexPos(MOVE_RIGHT, mapOfObjects) == 1)
      {
        this->move_x += 0.2f;
        this->body_r_x += 0.3f;
        player_direction = MOVE_RIGHT;
        this->currentDirection = MOVE_RIGHT;
        return (1);
      }
      else
      {
        this->body_r_x += 0.2f;
      }
    }
    else if (keys.input() == LEFT)
    {
			// sound.playFX(BB8_MISC);
      if (this->checkNexPos(MOVE_LEFT, mapOfObjects) == 1)
      {
        this->move_x -= 0.2f;
        this->body_r_x -= 0.3f;
        player_direction = MOVE_LEFT;
        this->currentDirection = MOVE_LEFT;        
        return (1);
      }
      else
        this->body_r_x -= 0.3f;
    }
    else
    {
      this->body_r_x = 0.0f; //Reseting body rotation
      this->body_r_y = 0.0f;
    }
    return (-1);
}

//Getting current position of the player
std::vector<int>  Player::getPlayerPos(std::vector<std::vector<int> >  mapOfObjects)
{
  int player_found = 0;

  for (unsigned int i = 0; i < mapOfObjects.size(); i++)
  {
    for (unsigned int j = 0; j < mapOfObjects[i].size(); j++)
    {
      if (mapOfObjects[i][j] == 3)
      {
        player_found = 1;
        this->playerPos.clear();
        this->playerPos.push_back(j);
        this->playerPos.push_back(i);
        break;
      }
    }
    if (player_found == 1)
      break;
  }
  return (this->playerPos);
}

bool  Player::checkForEnemies(std::vector<std::vector<int> > map)
{
  bool  player_found = false;
  
  for (unsigned int i = 0; i < map.size(); i++)
  {
    for (unsigned int j = 0; j < map[i].size(); j++)
    {
      if (map[i][j] == 3)
      {
        if (map[i][j + 1] >= 50) // CHECK RIGHT
          return (true);
        else if (map[i][j - 1] >= 50) // CHECK LEFT
          return (true);
        else if (map[i - 1][j] >= 50) // CHECK UP
          return (true);
        else if (map[i + 1][j] >= 50) // CHECK DOWN
          return (true);
        player_found = true;
        break;
      }
    }
    if (player_found)
      break;
  }
  return (false);
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
      (mapOfObjects[y_player_pos - 1][x_player_pos] != 4) &&
      (mapOfObjects[y_player_pos - 1][x_player_pos] < 50))
    {
      // std::cout << "Next Pos: " << mapOfObjects[y_player_pos - 1][x_player_pos] << std::endl;
      //Storing new player position
      if (this->n_enemies > 0 && mapOfObjects[y_player_pos - 1][x_player_pos] == 6)
      {
        return (-1);
      }
      else if (!this->portal && mapOfObjects[y_player_pos - 1][x_player_pos] == 6)
      {
        return (-1);
      }
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
      (mapOfObjects[y_player_pos + 1][x_player_pos] != 4) &&
      (mapOfObjects[y_player_pos + 1][x_player_pos] < 50))
    {
      // std::cout << "Next Pos: " << mapOfObjects[y_player_pos - 1][x_player_pos] << std::endl;
      //Storing new player position
      if (this->n_enemies > 0 && mapOfObjects[y_player_pos + 1][x_player_pos] == 6)
      {
        return (-1);
      }
      else if (!this->portal && mapOfObjects[y_player_pos + 1][x_player_pos] == 6)
      {
        return (-1);
      }
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

    if ((mapOfObjects[y_player_pos][x_player_pos - 1] != 1) &&
      (mapOfObjects[y_player_pos][x_player_pos - 1] != 2) &&
      (mapOfObjects[y_player_pos][x_player_pos - 1] != 4) &&
      (mapOfObjects[y_player_pos][x_player_pos - 1] < 50))
    {
      //Storing new player position
      if (this->n_enemies > 0 && mapOfObjects[y_player_pos][x_player_pos - 1] == 6)
      {
        return (-1);
      }
      else if (!this->portal && mapOfObjects[y_player_pos][x_player_pos - 1] == 6)
      {
        return (-1);
      }
      this->NewPlayerPos.clear();
      this->NewPlayerPos.push_back(x_player_pos - 1);
      this->NewPlayerPos.push_back(y_player_pos);

      return (1);
    }
  }
  if (direction == MOVE_RIGHT)
  {
    this->getPlayerPos(mapOfObjects);
    x_player_pos = this->playerPos[0];
    y_player_pos = this->playerPos[1];

    if ((mapOfObjects[y_player_pos][x_player_pos + 1] != 1) &&
      (mapOfObjects[y_player_pos][x_player_pos + 1] != 2) &&
      (mapOfObjects[y_player_pos][x_player_pos + 1] != 4) &&
      (mapOfObjects[y_player_pos][x_player_pos + 1] < 50))
    {
      if (this->n_enemies > 0 && mapOfObjects[y_player_pos][x_player_pos + 1] == 6)
      {
        return (-1);
      }
      else if (!this->portal && mapOfObjects[y_player_pos][x_player_pos + 1] == 6)
      {
        return (-1);
      }
      //Storing new player position
      this->NewPlayerPos.clear();
      this->NewPlayerPos.push_back(x_player_pos + 1);
      this->NewPlayerPos.push_back(y_player_pos);

      return (1);
    }
  }
  return (-1);
}

void  Player::setPcoords(float pos_x, float pos_y)
{
  this->move_x = pos_x;
  this->move_y = pos_y;
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

void  Player::setNextStage(int n_enemies, bool & changeStage, std::vector<std::vector<int> > map, bool portal)
{
  bool  portal_found = false;
  this->n_enemies = n_enemies;
  this->portal = portal;

  if (this->portal)
  {
    if (n_enemies < 1)
    {
      for (unsigned int i = 0; i < map.size(); i++)
      {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
          if (map[i][j] == 3)
          {
            if (this->currentDirection == MOVE_UP && map[i - 1][j] == 6)
            {
              changeStage = true;
              portal_found = true;
              break;
            }
            if (this->currentDirection == MOVE_DOWN && map[i + 1][j] == 6)
            {
              changeStage = true;
              portal_found = true;
              break;
            }
            if (this->currentDirection == MOVE_LEFT && map[i][j - 1] == 6)
            {
              changeStage = true;
              portal_found = true;
              break;
            }
            if (this->currentDirection == MOVE_RIGHT && map[i][j + 1] == 6)
            {
              changeStage = true;
              portal_found = true;
              break;
            }
          }
        }
        if (portal_found)
          break;
      }
    }
  }
}