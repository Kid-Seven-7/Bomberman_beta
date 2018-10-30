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
    this->changeDirection = false;
    this->direction = -1;
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

void    Enemy::drawEnemyRight(std::vector<std::vector<int> > & map)
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
            if (this->animeLoc)
            {
                this->pos_x += 0.0005f;
                if ((this->pos_x + 0.0005f) > this->nextXCoord)
                {
                    this->updateLoc = true;
                    this->animeLoc = false;
                    this->pos_x += 0.0005f;
                }
            }
        }
        else if (this->updateLoc)
        {
            if (map[this->getObjYCoord()][this->getObjXCoord() + 1] != 1)
            {
                map[this->getObjYCoord()][this->getObjXCoord() + 1] = this->getEnemyNumber();
                map[this->getObjYCoord()][this->getObjXCoord()] = 0;
                this->setObjCoords(this->getObjXCoord() + 1, this->getObjYCoord());
                this->updateLoc = false;
                if (map[this->getObjYCoord()][this->getObjXCoord() + 1] != 0)
                {
                    //CHANGE DIRECTION
                    this->changeDirection = true;
                }
                else
                {
                    this->animeLoc = true;
                    this->nextXCoord = this->pos_x + 1.45f;
                }
            }
        }
        else
        {
            this->nextXCoord = this->pos_x + 1.45f;
        }
    }
    enemy = glm::scale(enemy, glm::vec3(0.6f, 0.6f, 0.6f));
    this->shader.setMat4("model", enemy);
    this->enemy_model.Draw(this->shader);
}

void    Enemy::drawEnemyLeft(std::vector<std::vector<int> > & map)
{
    
    //MOVE X BY 1.45f
    //float)glfwGetTime()
    
    //RENDERS ENEMY ON THE SCREEN
    glm::mat4   enemy = glm::mat4(1.0f);

    //ENEMY DIRECTION
    if (this->direction == CHECK_LEFT)
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
            if (this->animeLoc)
            {
                this->pos_x -= 0.0005f;
                if ((this->pos_x - 0.0005f) < this->nextXCoord)
                {
                    this->updateLoc = true;
                    this->animeLoc = false;
                    this->pos_x -= 0.0005f;
                }
            }
        }
        else if (this->updateLoc)
        {
            if (map[this->getObjYCoord()][this->getObjXCoord() - 1] != 1)
            {
                map[this->getObjYCoord()][this->getObjXCoord() - 1] = this->getEnemyNumber();
                map[this->getObjYCoord()][this->getObjXCoord()] = 0;
                this->setObjCoords(this->getObjXCoord() - 1, this->getObjYCoord());
                this->updateLoc = false;
                if (map[this->getObjYCoord()][this->getObjXCoord() - 1] != 0)
                {
                    //CHANGE DIRECTION
                    this->changeDirection = true;
                }
                else
                {
                    this->animeLoc = true;
                    this->nextXCoord = this->pos_x - 1.45f;
                }
            }
        }
        else
        {
            this->nextXCoord = this->pos_x - 1.45f;
        }
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
        this->direction = CHECK_RIGHT;
    }
    else if (this->changeDirection)
    {
        this->check_possible_directions(map);
        this->direction = this->choosePath();
        this->animeLoc = true;
        this->changeDirection = false;
    }
    
    //DRAW ACCORDING TO DIRECTION
    if (this->direction == CHECK_RIGHT)
    {
        this->drawEnemyRight(map);
    }
    else if (this->direction == CHECK_LEFT)
    {
        this->drawEnemyLeft(map);
    }
}

void    Enemy::check_possible_directions(std::vector<std::vector<int> > map)
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