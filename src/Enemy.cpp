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
    {
        this->enemy_model = Model("bomberman_assets/enemies/ball driod1.obj");
        this->nextMoveCounter = 1500;
    }
    else if (level == 2) //Level 2 Enemy model
    {
        this->enemy_model = Model("bomberman_assets/enemies/drone.obj");
        this->nextMoveCounter = 1000;
    }
    else if (level >= 3) //Level 3 Enemy model
    {
        this->enemy_model = Model("bomberman_assets/enemies/og-driod.obj");
        this->nextMoveCounter = 800;
    }

    //Enemy movement

    this->enemyNumber = enemyNumber;
    //Enemy shader
    this->shader = shader;
    this->updateLoc = false;
    this->animeLoc = false;
    this->changeDirection = false;
    this->direction = -1;

    //NEXT POINT IN THE MAP
    this->moveCounter = 0;
    this->killPlayer = false;   
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
    if (this->moveCounter < this->nextMoveCounter)
    {
        if ((this->moveCounter + 1) >= this->nextMoveCounter)
        {
            this->moveCounter = 0;
            this->updateLoc = true;
        }
        this->moveCounter++;
    }
}

void    Enemy::drawEnemy()
{
    //RENDERS ENEMY ON THE SCREEN
    glm::mat4   enemy = glm::mat4(1.0f);

    //ENEMY DIRECTION
    if (this->direction == CHECK_RIGHT)
    {
        enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));
        enemy = glm::rotate(enemy, DIRECTION_RIGHT ,glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (this->direction == CHECK_LEFT)
    {
        enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));
        enemy = glm::rotate(enemy, DIRECTION_LEFT ,glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (this->direction == CHECK_UP)
    {
        enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));
        enemy = glm::rotate(enemy, DIRECTION_UP ,glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (this->direction == CHECK_DOWN)
    {
        enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));
        enemy = glm::rotate(enemy, DIRECTION_DOWN ,glm::vec3(0.0f, 1.0f, 0.0f));
    }
    enemy = glm::scale(enemy, glm::vec3(0.6f, 0.6f, 0.6f));
    this->shader.setMat4("model", enemy);
    this->enemy_model.Draw(this->shader);
}

Enemy::~Enemy() {}

void    Enemy::enemyAI(std::vector<std::vector<int> > & map)
{
   if (this->direction == -1)
   {
       this->check_possible_directions(map);
       this->direction = this->choosePath();
   }
   else
   {
       if (!this->checkDirection(map))
       {
           this->check_possible_directions(map);
           this->direction = this->choosePath();
       }
   }
   if (this->updateLoc)
        this->updateEnemyLocation(map);
   this->move();
   this->drawEnemy();
}

bool    Enemy::checkDirection(std::vector<std::vector<int> > map)
{
    bool    directionSafe = false;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == this->getEnemyNumber())
            {
                if ((map[i][j + 1] == 0 || map[i][j + 1] == 3) && this->direction == CHECK_RIGHT) // RIGHT
                {
                    if (map[i][j + 1] == 3)
                        this->killPlayer = true;
                    directionSafe = true;
                    break;
                }
                if ((map[i][j - 1] == 0 || map[i][j - 1] == 3) && this->direction == CHECK_LEFT) // LEFT
                {
                    if (map[i][j - 1] == 3)
                        this->killPlayer = true;
                    directionSafe = true;
                    break;
                }
                if ((map[i - 1][j] == 0 || map[i - 1][j] == 3) && this->direction == CHECK_UP) // UP
                {
                    if (map[i - 1][j] == 3)
                        this->killPlayer = true;
                    directionSafe = true;
                    break;
                }
                if ((map[i + 1][j] == 0 || map[i + 1][j] == 3) && this->direction == CHECK_DOWN) //DOWN
                {
                    if (map[i + 1][j] == 3)
                        this->killPlayer = true;
                    directionSafe = true;
                    break;
                }
            }
        }
        if (directionSafe)
            break;
    }

    return (directionSafe);
}

void    Enemy::updateEnemyLocation(std::vector<std::vector<int> > & map)
{
    if (this->direction == CHECK_RIGHT)
    {
        if (this->checkDirection(map))
        {
            map[this->getObjYCoord()][this->getObjXCoord() + 1] = this->getEnemyNumber();
            map[this->getObjYCoord()][this->getObjXCoord()] = 0;
            this->setObjCoords(this->getObjXCoord() + 1, this->getObjYCoord());

            this->pos_x += 1.45f;
            this->updateLoc = false;
        }
    }
    else if (this->direction == CHECK_LEFT)
    {
        if (this->checkDirection(map))
        {
            map[this->getObjYCoord()][this->getObjXCoord() - 1] = this->getEnemyNumber();
            map[this->getObjYCoord()][this->getObjXCoord()] = 0;
            this->setObjCoords(this->getObjXCoord() - 1, this->getObjYCoord());

            this->pos_x -= 1.45f;
            this->updateLoc = false;   
        }
    }
    else if (this->direction == CHECK_UP)
    {
        if (this->checkDirection(map))
        {
            map[this->getObjYCoord() - 1][this->getObjXCoord()] = this->getEnemyNumber();
            map[this->getObjYCoord()][this->getObjXCoord()] = 0;
            this->setObjCoords(this->getObjXCoord(), this->getObjYCoord() - 1);
            
            this->pos_y -= 1.3f;
            this->updateLoc = false;   
        }
    }
    else if (this->direction == CHECK_DOWN)
    {
        if (this->checkDirection(map))
        {
            map[this->getObjYCoord() + 1][this->getObjXCoord()] = this->getEnemyNumber();
            map[this->getObjYCoord()][this->getObjXCoord()] = 0;
            this->setObjCoords(this->getObjXCoord(), this->getObjYCoord() + 1);

            this->pos_y += 1.3f;
            this->updateLoc = false;   
        }
    }
}

void    Enemy::check_possible_directions(std::vector<std::vector<int> > map)
{
    bool    enemyFound = false;
    bool    no_path = true;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == this->getEnemyNumber())
            {
                this->possible_directions.clear();
                if (map[i][j + 1] == 0 || map[i][j + 1] == 3) // RIGHT
                {
                    this->possible_directions.push_back(CHECK_RIGHT);
                    no_path = false;
                }
                if (map[i][j - 1] == 0 || map[i][j - 1] == 3) // LEFT
                {
                    this->possible_directions.push_back(CHECK_LEFT);
                    no_path = false;
                }
                if (map[i - 1][j] == 0 || map[i - 1][j] == 3) // UP
                {
                    this->possible_directions.push_back(CHECK_UP);
                    no_path = false;
                }
                if (map[i + 1][j] == 0 || map[i + 1][j] == 3) // DOWN
                {
                    this->possible_directions.push_back(CHECK_DOWN);
                    no_path = false;
                }
                if (no_path)
                {
                    this->possible_directions.push_back(CHECK_RIGHT);
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

void    Enemy::setKillPlayerValue(bool  killPlayer)
{
    this->killPlayer = killPlayer;
}

bool    Enemy::getKillPlayerValue()
{
    return (this->killPlayer);
}