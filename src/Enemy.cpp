/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:09:02 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/19 14:26:09 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/Enemy.hpp"

Enemy::Enemy() {}

Enemy::Enemy(int enemyNumber, Shader shader, int level)
{
    //ENEMIES CHANGE WITH LEVELS

    if (level == 1) //Level 1 Enemy model
        this->enemy_model = Model("bomberman_assets/enemies/ball driod1.obj");
    if (level == 2) //Level 2 Enemy model
        this->enemy_model = Model("bomberman_assets/enemies/drone.obj");
    if (level == 3) //Level 3 Enemy model
        this->enemy_model = Model("bomberman_assets/enemies/og-driod.obj");

    //Enemy movement
    // this->pos_x = pos_x;
    // this->pos_y = pos_y;

    this->enemyNumber = enemyNumber;
    //Enemy shader
    this->shader = shader;
}

void    Enemy::setObjCoords(int obj_x, int obj_y)
{
    //SETTING THE OBJ COORDS
    this->obj_pos_x = obj_x;
    this->obj_pos_y = obj_y;
}

void    Enemy::setPosCoords(float pos_x, float pos_y)
{
    //SETTING THE POSITION COORDS
    this->pos_x = pos_x;
    this->pos_y = pos_y;

    // std::cout << "POS_X: " << this->pos_x << " POS_Y: " << this->pos_y << std::endl;
    // exit(1);
}

int     Enemy::getEnemyNumber() 
{
    //RETURNS ENEMY NUMBER TO USE INCASE OF DEFEAT
    return (enemyNumber);
}

void    Enemy::setEnemyDirection(int direction)
{
    //RETURNS THE CURRENT DIRECTION OF THE ENEMY
    this->direction = direction;
}

void    Enemy::move()
{
    //UPDATES ENEMY MOVEMENT
}

void    Enemy::drawEnemy()
{
    //MOVE X BY 1.45f
    //glm::vec3((float)glfwGetTime() + 

    //RENDERS ENEMY ON THE SCREEN
    glm::mat4   enemy = glm::mat4(1.0f);
    // std::cout << "X Coord: " << this->pos_x << " Y Coord: " << this->pos_y << std::endl;

    enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));

    //ENEMY DIRECTION
    if (this->direction == CHECK_UP)
        enemy = glm::rotate(enemy, DIRECTION_UP ,glm::vec3(0.0f, 1.0f, 0.0f));
    if (this->direction == CHECK_RIGHT)
        enemy = glm::rotate(enemy, DIRECTION_RIGHT ,glm::vec3(0.0f, 1.0f, 0.0f));
    if (this->direction == CHECK_DOWN)
        enemy = glm::rotate(enemy, DIRECTION_DOWN ,glm::vec3(0.0f, 1.0f, 0.0f));
    if (this->direction == CHECK_LEFT)
        enemy = glm::rotate(enemy, DIRECTION_LEFT ,glm::vec3(0.0f, 1.0f, 0.0f));

    enemy = glm::scale(enemy, glm::vec3(0.6f, 0.6f, 0.6f));

    this->shader.setMat4("model", enemy);
    this->enemy_model.Draw(this->shader);
}

Enemy::~Enemy() {}

void    Enemy::enemyAI(std::vector<std::vector<int> > & map)
{
    this->check_if_empty(map);
    this->setEnemyDirection(this->choosePath());
    // this->updateMap(map);
    this->drawEnemy();
}

// void    Enemy::updateMap(std::vector<std::vector<int> > & map)
// {
//     //UPDATING ENEMY MOVEMENT ON THE MAP

//     //Current Coordinates
//     float   curXCoord = getXCoord();
//     float   curYCoord = getYCoord();
// }

void    Enemy::check_if_empty(std::vector<std::vector<int> > map)
{
    bool    enemyFound = false;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == this->getEnemyNumber())
            {
                this->possible_directions.clear();
                if (map[i][j + 1] == 0) // RIGHT
                {
                    this->possible_directions.push_back(CHECK_RIGHT);
                }
                if (map[i][j - 1] == 0) // LEFT
                {
                    this->possible_directions.push_back(CHECK_LEFT);
                }
                if (map[i + 1][j] == 0) // DOWN
                {
                    this->possible_directions.push_back(CHECK_DOWN);
                }
                if (map[i - 1][j] == 0) //UP
                {
                    this->possible_directions.push_back(CHECK_UP);
                }
                enemyFound = true;
                break;
            }
        }
        if (enemyFound)
            break;
    }
}

int     Enemy::choosePath()
{
    srand(time(NULL));

    int randPath = rand() % (int)this->possible_directions.size();
    return (this->possible_directions[(unsigned int)randPath]);
}

int     Enemy::getObjXCoord() { return (this->obj_pos_x); }

int     Enemy::getObjYCoord() { return (this->obj_pos_y); }

float   Enemy::getXCoord() { return (this->pos_x); }

float   Enemy::getYCoord() { return (this->pos_y); }