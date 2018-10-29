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
    else if (level == 2) //Level 2 Enemy model
        this->enemy_model = Model("bomberman_assets/enemies/drone.obj");
    else if (level == 3) //Level 3 Enemy model
        this->enemy_model = Model("bomberman_assets/enemies/og-driod.obj");

    //Enemy movement
    // this->pos_x = pos_x;
    // this->pos_y = pos_y;

    this->enemyNumber = enemyNumber;
    //Enemy shader
    this->shader = shader;
    this->updateLoc = false;
    this->animeLoc = false;
    this->animeDone = false;
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
    this->nextXCoord = -1.0f;
    this->nextYCoord = -1.0f;
    

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
    //float)glfwGetTime()
    
    //RENDERS ENEMY ON THE SCREEN
    glm::mat4   enemy = glm::mat4(1.0f);

    //ENEMY DIRECTION
    if (this->direction == CHECK_RIGHT)
    {
        if (this->nextXCoord < 0)
        {
            this->nextXCoord = this->pos_x + 1.45f;
            this->animeLoc = true;
        }
        enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));
        enemy = glm::rotate(enemy, DIRECTION_RIGHT ,glm::vec3(0.0f, 1.0f, 0.0f));
        if (this->pos_x < this->nextXCoord)
        {
            if (animeLoc)
            {
                this->pos_x += 0.0005f;
                if ((this->pos_x + 0.0005f) > this->nextXCoord)
                {
                    this->updateLoc = true;
                    this->animeDone = true;
                    animeLoc = false;
                    this->pos_x += 0.0005f;
                }
            }
        }
        else
        {
            this->updateLoc = true;            
            this->nextXCoord = this->pos_x + 1.45f;
        }

    }
    else if (this->direction == CHECK_LEFT)
    {
        if (this->nextXCoord < 0)
        {
            this->nextXCoord = this->pos_x - 1.45f;
            this->animeLoc = true;
        }
        enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));
        enemy = glm::rotate(enemy, DIRECTION_LEFT ,glm::vec3(0.0f, 1.0f, 0.0f));
        if (this->pos_x > this->nextXCoord)
        {
            if (animeLoc)
            {
                this->pos_x -= 0.0005f;
                if ((this->pos_x - 0.0005f) < this->nextXCoord)
                {
                    this->updateLoc = true;
                    animeLoc = false;
                    this->pos_x -= 0.0005f;
                }
            }
        }
        else
        {
            this->updateLoc = true;            
            this->nextXCoord = this->pos_x - 1.45f;
            // std::cout << "Next X Coord: " << this->nextXCoord << std::endl;
        }
    }
    else if (this->direction == CHECK_UP)
    {
        if (this->nextYCoord < 0)
        {
            this->animeLoc = true;
            this->nextYCoord = this->pos_y - 1.3f;
        }
        enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));
        enemy = glm::rotate(enemy, DIRECTION_UP ,glm::vec3(0.0f, 1.0f, 0.0f));
        if (this->pos_y > this->nextYCoord)
        {
            if (animeLoc)
            {
                this->pos_y -= 0.0005f;
                
                if ((this->pos_y - 0.0005f) < this->nextYCoord)
                {
                    this->updateLoc = true;
                    animeLoc = false;
                    this->pos_y -= 0.0005f;
                }
            }
        }
        else
        {
            this->updateLoc = true;            
            this->nextYCoord = this->pos_y - 1.3f;
        }
    }
    else if (this->direction == CHECK_DOWN)
    {
        if (this->nextYCoord < 0)
        {
            this->nextYCoord = this->pos_y + 1.3f;
            this->animeLoc = true;
        }
        enemy = glm::translate(enemy, glm::vec3(this->pos_x - 3.3f, -0.85f, this->pos_y - 1.85f));
        enemy = glm::rotate(enemy, DIRECTION_DOWN ,glm::vec3(0.0f, 1.0f, 0.0f));
        if (this->pos_y < this->nextYCoord)
        {
            if (animeLoc)
            {
                this->pos_y += 0.0005f;
                if ((this->pos_y - 0.0005f) > this->nextYCoord)
                {
                    this->updateLoc = true;
                    animeLoc = false;
                    this->pos_y += 0.0005f;
                }
            }
        }
        else
        {
            this->updateLoc = true;            
            this->nextYCoord = this->pos_y + 1.3f;
            // std::cout << "Next Y Coord: " << this->nextYCoord << std::endl;
        }
    }
    enemy = glm::scale(enemy, glm::vec3(0.6f, 0.6f, 0.6f));

    this->shader.setMat4("model", enemy);
    this->enemy_model.Draw(this->shader);
}

Enemy::~Enemy() {}

void    Enemy::enemyAI(std::vector<std::vector<int> > & map)
{
    this->check_if_empty(map);
    if (this->checkDirection(map, this->direction))
    {
        this->updateMap(map);
        //PUT MAP MOVEMENT PATCH HERE
        if (this->animeDone)
        {
            this->mapPatch(map);
            this->animeDone = false;
        }
    }
    else
    {
        this->setEnemyDirection(this->choosePath());
    }
    this->drawEnemy();
}

void    Enemy::mapPatch(std::vector<std::vector<int> > & map)
{
    bool    enemyFound = false;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == this->getEnemyNumber())
            {
                if ((map[i][j + 1] == 1 || map[i][j + 1] == 2) && 
                    (this->direction == CHECK_RIGHT)) // RIGHT
                {
                    this->nextXCoord = this->pos_x + 1.45f;
                    this->animeLoc = true;
                    this->updateLoc = true;
                    std::cout << std::endl;
                    std::cout << "IN LOCATION: " << map[i][j + 2] << std::endl;
                    this->drawEnemy();
                    // usleep(999999);
                    // exit(0);
                }
                else if ((map[i][j - 1] == 1 || map[i][j - 1] == 2) && 
                    (this->direction == CHECK_LEFT)) // LEFT
                {
                    std::cout << std::endl;
                    std::cout << "IN LOCATION: " << map[i][j - 1] << std::endl;
                    usleep(999999);
                    exit(0);
                }
                else if ((map[i + 1][j] == 1 || map[i + 1][j] == 2) && 
                    (this->direction == CHECK_DOWN)) // DOWN
                {
                    std::cout << std::endl;
                    std::cout << "IN LOCATION: " << map[i + 1][j] << std::endl;
                    usleep(999999);
                    exit(0);
                }
                else if ((map[i - 1][j] == 1 || map[i - 1][j] == 2) && 
                    (this->direction == CHECK_UP)) //UP
                {
                    std::cout << std::endl;
                    std::cout << "IN LOCATION: " << map[i - 1][j] << std::endl;
                    usleep(999999);
                    exit(0);
                }
                enemyFound = true;
                break;
            }
        }
        if (enemyFound)
            break;
    }
}

void    Enemy::updateMap(std::vector<std::vector<int> > & map)
{
    if (this->updateLoc)
    {
        if (this->direction == CHECK_RIGHT)
        {
            // std::cout << "DIRECTION: " << this->direction << std::endl;
            map[this->getObjYCoord()][this->getObjXCoord() + 1] = this->enemyNumber;
            map[this->getObjYCoord()][this->getObjXCoord()] = 0;
            this->setObjCoords(this->getObjXCoord() + 1, this->getObjYCoord());
            this->updateLoc = false;
            this->animeLoc = true;
        }
        else if (this->direction == CHECK_LEFT)
        {
            // std::cout << "DIRECTION: " << this->direction << std::endl;
            map[this->getObjYCoord()][this->getObjXCoord() - 1] = this->enemyNumber;
            map[this->getObjYCoord()][this->getObjXCoord()] = 0;
            this->setObjCoords(this->getObjXCoord() - 1, this->getObjYCoord());
            this->updateLoc = false;
            this->animeLoc = true;
        }
        else if (this->direction == CHECK_UP)
        {
            // std::cout << "DIRECTION: " << this->direction << std::endl;
            map[this->getObjYCoord() - 1][this->getObjXCoord()] = this->enemyNumber;
            map[this->getObjYCoord()][this->getObjXCoord()] = 0;
            this->setObjCoords(this->getObjXCoord(), this->getObjYCoord() - 1);
            this->updateLoc = false;
            this->animeLoc = true;
        }
        else if (this->direction == CHECK_DOWN)
        {
            // std::cout << "DIRECTION: " << this->direction << std::endl;
            map[this->getObjYCoord() + 1][this->getObjXCoord()] = this->enemyNumber;
            map[this->getObjYCoord()][this->getObjXCoord()] = 0;
            this->setObjCoords(this->getObjXCoord(), this->getObjYCoord() + 1);
            this->updateLoc = false;
            this->animeLoc = true;
        }
    }
}

void    Enemy::check_if_empty(std::vector<std::vector<int> > map)
{
    int static check_counter = 0;
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
                    // if (check_counter > 2)
                    // {
                    //     std::cout << "NEXT OBJ: " << map[i][j + 3] << std::endl;
                    //     exit(0);
                    // }
                    check_counter++;
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

bool    Enemy::checkDirection(std::vector<std::vector<int> > map, int direction)
{
    bool    direction_safe = false;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == this->getEnemyNumber())
            {
                if (direction == CHECK_RIGHT)
                {
                    if (map[i][j + 1] == 0)
                    {
                        direction_safe = true;
                        break;
                    }
                    else
                    {
                        if (map[i][j + 1] == 1)
                        {
                            std::cout << "Current Location: " << map[i][j] << std::endl;
                            exit(0);
                        }
                    }
                }
                else if (direction == CHECK_LEFT)
                {
                    if (map[i][j - 1] == 0)
                    {
                        direction_safe = true;
                        break;
                    }
                }
                else if (direction == CHECK_UP)
                {
                    if (map[i - 1][j] == 0)
                    {
                        direction_safe = true;
                        break;
                    }
                }
                else if (direction == CHECK_DOWN)
                {
                    if (map[i + 1][j] == 0)
                    {
                        direction_safe = true;
                        break;
                    }
                }
            }
        }
        if (direction_safe)
            break;
    }

    return (direction_safe);
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