/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsEngine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:29:25 by amatshiy          #+#    #+#             */
/*   Updated: 2018/11/03 03:09:45 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine()
{
    if (!glfwInit())
    {
        std::cout << "GLFW failed to start" << std::endl;
        exit(1);
    }
    this->glfwConfig();
    this->gladConfg();

    //Variable Init
    this->ourShader = Shader("Shaders/texture.vs", "Shaders/texture.fs");
    glEnable(GL_DEPTH_TEST);

    //Initializing current map
    this->currentMap = 1;
    this->deletePlayer = false;

    //Default player direction
     this->player_direction = -1;
     this->cam = CameraClass();
     this->deleteEnemy = false;
     this->currentEnemy = 0;
     this->skipMapUpdate = false;
     this->restart_game = false;
     this->isDoor = false;
     this->changeStage = false;
}

GraphicsEngine::GraphicsEngine(GLFWwindow  *window)
{
	this->window = window;
    // this->glfwConfig();
	this->gladConfg();

	//Variable Init
	this->ourShader = Shader("Shaders/texture.vs", "Shaders/texture.fs");
	glEnable(GL_DEPTH_TEST);

	//Initializing current map
	this->currentMap = 1;
    this->deletePlayer = false;


    //Default player direction
     this->player_direction = -1;
     this->cam = CameraClass();
     this->deleteEnemy = false;
     this->currentEnemy = 0;
     this->skipMapUpdate = false;
     this->restart_game = false;
     this->isDoor = false;
     this->changeStage = false;
}

GraphicsEngine::~GraphicsEngine()
{
    // glfwTerminate();
}

void    GraphicsEngine::glfwConfig()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #endif

    this->window = glfwCreateWindow(WIDTH, HEIGHT, "Bomberman 42", NULL, NULL);

    if (!this->window){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    //Making the window the current context
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //For screen resolution
}

void    GraphicsEngine::gladConfg()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

void    GraphicsEngine::MainControl(Sound &sound, Keys &keys, int level)
{
    //Game Settings Sway
    glfwSetTime(0.1f); 
    this->currentMap = level;

    //Init things 
    Player          player;
    Model_Objects   model_object;
    BombClass       bomb;
    // LoadingScreen   restartGame;
    int             bomb_counter = 0;
    int             pause_counter = 60;
    bool            start_counter = false;
    bool            reset_player = false;
    unsigned int    enemies_updated = 0;
    bool            resetAllObjs = false;
    int             resetAllCounter = 60;
    LoadingScreen   nextStageInit;
    int             counter = 0;

    //Physics Engine
    // PhysicsEngine p_engine; // remove this ENGINE BEFORE SUBMISSION

    //MapEngine Testing
    MapEngine m_engine;
    m_engine.getMapPaths("./maps");
    m_engine.convertMaps();

    std::vector<std::vector<std::vector<int>>> maps = m_engine.getObjectsMaps();
    std::vector<std::vector<int> > old_map = maps[this->currentMap];

    if (this->createEnemyArray(maps[this->currentMap], 4))
    {
        //CHECKING IF THERE ARE ENEMIES ON THE MAP OF OBJS
        if (this->enemyNumbers.size() < 1)
        {
            std::cout << RED << "Error: " << NC << "Couldn't find any enemies on the map." << std::endl;
            std::cout << GREEN << "Info: " << NC << "Terminating application..." << std::endl;
            exit(1);
        }

        //create enemies
        for (unsigned int x = 0; x < this->enemyNumbers.size(); x++)
        {
            Enemy enemy = Enemy(this->enemyNumbers[x][0], ourShader, 1);
            enemy.setObjCoords(this->enemyNumbers[x][1], this->enemyNumbers[x][2]); //SETTING ENEMY OBJ COORDS
            this->enemies.push_back(enemy);
        }
    }

    std::cout << GREEN << "info: " << NC << "Loading resources" << std::endl;
    // usleep(100000);
    while (!glfwWindowShouldClose(this->window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!this->changeStage)
        {
            //input process
            if (processInput(keys))
            {
                m_engine.dumpCurrentMap(this->currentMap);
                std::ofstream file("gameState/playerCoords.txt");
                file << "Player data\n" << player.getXcoord() << ":" << player.getYcoord() << std::endl;
                cam.saveinfo();
                displayStart(sound, keys, window);
                glEnable(GL_DEPTH_TEST);
            }


            //Start of rendering...
            this->modelProjectionConfig();
            model_object.universe_func(ourShader);
            model_object.ClockModel(ourShader);
            model_object.Score(ourShader);
            model_object.ClockHand(ourShader);
            model_object.Engine(ourShader, 3.95f, -28.5f);
            model_object.Engine(ourShader, 4.15f, 35.5f);
            model_object.Engine(ourShader, 37.5f, 4.15f);
            model_object.Engine(ourShader, -27.5f, 4.15f);
            model_object.base_func(ourShader);

            for (unsigned int j = 0; j < maps[this->currentMap].size(); j++)
            {
                for (unsigned int i = 0; i < maps[this->currentMap][j].size(); i++)
                {
                    if (maps[this->currentMap][j][i] == HARD_WALL)
                    {
                        // std::cout << this->pos_x << " " << this->pos_y << " ";
                        // std::cout << maps[this->currentMap][j][i] << " ";
                        model_object.hard_wall_func(this->ourShader, this->pos_x, this->pos_y);
                    }
                    if (maps[this->currentMap][j][i] == SOFT_WALL)
                    {
                        // std::cout << this->pos_x << " " << this->pos_y << " ";
                        // std::cout << maps[this->currentMap][j][i] << " ";
                        model_object.soft_wall_func(this->ourShader, this->pos_x, this->pos_y);
                    }
                    if (maps[this->currentMap][j][i] == DOOR)
                    {
                        // std::cout << this->pos_x << " " << this->pos_y << " ";
                        // std::cout << maps[this->currentMap][j][i] << " ";
                        if (this->isDoor)
                        {
                            model_object.PortalDoor(this->ourShader, this->pos_x, this->pos_y);
                        }
                        else
                            model_object.soft_wall_func(this->ourShader, this->pos_x, this->pos_y);
                    }
                    if (maps[this->currentMap][j][i] == FLOOR)
                    {
                        // std::cout << this->pos_x << " " << this->pos_y << " ";
                        // std::cout << maps[this->currentMap][j][i] << " ";
                        //TODO
                    }
                    if (maps[this->currentMap][j][i] == PLAYER_OBJ)
                    {
                        // std::cout << this->pos_x << " " << this->pos_y << " ";
                        // std::cout << maps[this->currentMap][j][i] << " ";
                        //TODO
                    }
                    if (maps[this->currentMap][j][i] == 8)
                    {
                        // std::cout << this->pos_x << " " << this->pos_y << " ";
                        // std::cout << maps[this->currentMap][j][i] << " ";
                        model_object.player_life_func(this->ourShader, this->pos_x, this->pos_y);
                        model_object.headModel(this->ourShader, this->pos_x, this->pos_y);
                        //TODO
                    }
                    if (maps[this->currentMap][j][i] == BOMB)
                    {
                        // std::cout << this->pos_x << " " << this->pos_y << " ";
                        // std::cout << maps[this->currentMap][j][i] << " ";
                        //FIX BOMB CLASS!!!
                        //CALL ARRAY CHECK BEFORE PLACING BOMB
                        bomb.putBomb(ourShader, this->pos_x, this->pos_y, 1);
                        if (bomb_counter >= 75)
                            bomb.putBomb(ourShader, this->pos_x, this->pos_y, 2);
                    }
                    if (enemies_updated < this->enemies.size())
                    {
                        std::vector<float>  coords;
                        //UPDATING ENEMY POSITION COORDINATES
                        for (unsigned int x = 0; x < this->enemies.size(); x++)
                        {
                            if ((unsigned int)this->enemies[x].getObjXCoord() == i && 
                                (unsigned int)this->enemies[x].getObjYCoord() == j)
                            {
                                this->enemies[x].setPosCoords(this->pos_x + 1.4f, this->pos_y);
                                coords.push_back(this->pos_x + 1.4f);
                                coords.push_back(this->pos_y);

                                this->enemyCoords.push_back(coords);
                                enemies_updated++;
                            }
                        }
                    }
                    if (enemies_updated == this->enemies.size())
                    {
                        // exit(5);
                        //ENEMY MOVEMENTS SHOULD ALL HAPPEN HERE

                        if (!resetAllObjs)
                        {
                            for (unsigned int x = 0; x < this->enemies.size(); x++)
                            {
                                this->enemies[x].enemyAI(maps[this->currentMap]);
                                this->currentEnemy = x;

                                if (this->enemies[x].playerBeDead())
                                {
                                    player.setPcoords(0.0f, 0.0f);
                                    this->enemies[x].setPlayerState(false);
                                    this->reset_camera();
                                    reset_player = true;
                                    this->remove_life(maps[this->currentMap]);
                                    resetAllObjs = true;
                                    this->deletePlayer = true;
                                }
                            }
                        }
                    }
                    player.bodyModel(this->ourShader);
                    player.headModel(this->ourShader);
                    player.setNextStage(this->enemies.size(), this->changeStage , maps[this->currentMap], this->isDoor);

                    if ((this->pos_x + 1.4f) <  std::numeric_limits<float>::max() && 
                        (this->pos_x + 1.4f) < std::numeric_limits<float>::infinity())
                        this->pos_x += 1.4f;
                }

                //ENEMY DEATH THINGS
                if (bomb_counter == 75 && this->deleteEnemy)
                {
                    std::cout << "Number of enemies b4: " << this->enemies.size() << std::endl;
                    if (this->ft_deleteEnemy(this->bombXCoord, this->bombYCoord, maps[this->currentMap]))
                    {
                        for (unsigned int i = 0; i < this->enemies.size(); i++)
                        {
                            if (this->enemies.size() && this->enemies[i].getEnemyNumber() == this->currentDeletedEnemy)
                            {
                                if (this->enemies.size() == 0)
                                    break;
                                this->enemies.erase(this->enemies.begin() + i);
                                // if (this->enemyNumbers.size())
                                //     this->enemyNumbers.erase(this->enemyNumbers.begin() + 1);
                                enemies_updated--;
                            }
                        }
                    }
                    this->deleteEnemy = false;
                }

                // std::cout << "Player X: " << player.getXcoord() << std::endl;
                // std::cout << "Player Y: " << player.getYcoord() << std::endl;
                // std::cout << std::endl;
                if ((this->pos_y + 1.3f) < std::numeric_limits<float>::max() &&
                    (this->pos_y + 1.3f) < std::numeric_limits<float>::infinity())
                    this->pos_y += 1.3f;
                this->pos_x = 0.0f;
            }

            this->pos_y = 0.0f;

            if (start_counter)
                bomb_counter++;
            if (this->deletePlayer)
            {
                //Render Dead Screen
                for (int x = 0; x < 500; x++)
                {
                    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    model_object.universe_func(ourShader);
                    model_object.gameOverScreen(ourShader, 2);

                    //Clearing Buffer
                    glfwSwapBuffers(this->window);
                    glfwPollEvents();
                }

                for (int x = 0; x < 10; x++)
                {
                    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    model_object.universe_func(ourShader);
                    model_object.gameOverScreen(ourShader, 2);

                    //Clearing Buffer
                    glfwSwapBuffers(this->window);
                    glfwPollEvents();
                }
                //NEXT POSITION RESET
                nextXPos = 2.6f;
                nextYPos = 2.6f;
                prevXpos = -2.6f;
                prevYpos = -2.6f;
                this->currentMap = 0;

                counter = 0;
                glfwSetTime(0.1f);
                this->isDoor = false;
                displayStart(sound, keys, this->window);
            }
            if (bomb_counter == 75)
            {
                if (this->update_bomb_range(maps[this->currentMap]) == 3)
                {
                    this->remove_life(maps[this->currentMap]);
                    player.setPcoords(0.0f, 0.0f);
                    this->reset_player_location(maps[this->currentMap]);
                    this->reset_camera();
                    reset_player = true;
                    this->deletePlayer = true;

                    //Reseting bomb after player suicide
                    bomb_counter = 0;
                    start_counter = false;
                    this->remove_bomb(maps[this->currentMap]);
                    
                    //DESTROY
                    nextXPos = 2.6f;
                    nextYPos = 2.6f;
                    prevXpos = -2.6f;
                    prevYpos = -2.6f;

                    for (int x = 0; x < 200; x++)
                    {
                        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        model_object.universe_func(ourShader);
                        model_object.gameOverScreen(ourShader, 2);

                        //Clearing Buffer
                        glfwSwapBuffers(this->window);
                        glfwPollEvents();
                    }

                    counter = 0;
                    glfwSetTime(0.1f);
                    this->isDoor = false;
                    displayStart(sound, keys, this->window);
                }
            }
            if (bomb_counter >= 100)
            {
                bomb_counter = 0;
                start_counter = false;
                this->remove_bomb(maps[this->currentMap]);
            }
            if (reset_player)
            {
                if (pause_counter > 1)
                    pause_counter--;
                else
                {
                    pause_counter = 60;
                    reset_player = false;
                    bomb_counter = 0;
                    start_counter = false;
                    this->remove_bomb(maps[this->currentMap]);
                }
            }
            if (resetAllObjs)
            {
                if (resetAllCounter > 1)
                    resetAllCounter--;
                else
                {
                    resetAllCounter = 60;
                    resetAllObjs = false;
                    // usleep(999999);
                }
            }
            // glfwSwapBuffers(this->window);
            // glfwPollEvents();

            if (keys.input() == SPACE)
            {
                if (!(start_counter) && (this->array_check(maps[this->currentMap])))
                    start_counter = true;
            }
            if (pause_counter >= 60) // TODO :: ADD ANOTHER IF TO CHECK FOR THE PLAYER RESET AFTER ENEMY ATTACK
                if (resetAllCounter >= 60)
                    this->callMovementFunctions(player, sound, keys, maps[this->currentMap]);
            if (!this->skipMapUpdate)
            {
                this->updateMap(player, maps[this->currentMap]);
                m_engine.updateCurrentMap(currentMap, maps[this->currentMap]);
            }
            else
                this->skipMapUpdate = false;

            // if (this->changeStage)
            // {
            //     std::cout << "Change stage: " << this->changeStage << std::endl;
            // }
            // std::cout << "Current running code... 1" << std::endl;
        } //CHANGE STAGE IF STATEMENT ENDS HERE
        else
        {
            //RENDER WIN OR WHATEVER
            if (this->currentMap < 8)
                this->currentMap += 1;
            else
            {
                //Resetting Next Pos vars
                nextXPos = 2.6f;
                nextYPos = 2.6f;
                prevXpos = -2.6f;
                prevYpos = -2.6f;
                //Reset Player
                player.setPcoords(0.0f, 0.0f);
                
                for (int x = 0; x < 60; x++)
                {
                    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    model_object.universe_func(ourShader);
                    model_object.gameOverScreen(ourShader, 1);

                    //Clearing Buffer
                    glfwSwapBuffers(this->window);
                    glfwPollEvents();
                }
                counter = 0;
                model_object.~Model_Objects();
                glfwSetTime(0.1f);
                this->isDoor = false;
            }
            this->changeStage = false;

            //Resetting Next Pos vars
            nextXPos = 2.6f;
            nextYPos = 2.6f;
            prevXpos = -2.6f;
            prevYpos = -2.6f;
            //Reset Player
            player.setPcoords(0.0f, 0.0f);

            for (int x = 0; x < 60; x++)
            {
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                model_object.universe_func(ourShader);
                model_object.gameOverScreen(ourShader, 1);

                //Clearing Buffer
                glfwSwapBuffers(this->window);
                glfwPollEvents();
            }
            counter = 0;
            model_object.~Model_Objects();
            glfwSetTime(0.1f);
            this->isDoor = false;
            nextStageInit.LoadGame(this->window, sound, keys, this->currentMap);
        }
        //Clearing Buffer
        glfwSwapBuffers(this->window);
        glfwPollEvents();
        counter++;
        std::cout << "Counter: " << counter << std::endl;
        if (counter == 3550)
        {
            for (int x = 0; x < 200; x++)
            {
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                model_object.universe_func(ourShader);
                model_object.gameOverScreen(ourShader, 2);

                //Clearing Buffer
                glfwSwapBuffers(this->window);
                glfwPollEvents();
            }
            //NEXT POSITION RESET
            nextXPos = 2.6f;
            nextYPos = 2.6f;
            prevXpos = -2.6f;
            prevYpos = -2.6f;
            this->currentMap = 0;

            glfwSetTime(0.1f);
            counter = 0;
            this->isDoor = false;
            displayStart(sound, keys, this->window);   
        }
    }
    nextXPos = 2.6f;
    nextYPos = 2.6f;
    prevXpos = -2.6f;
    prevYpos = -2.6f;
}

bool    GraphicsEngine::ft_deleteEnemy(int x_pos, int y_pos, std::vector<std::vector<int> > & map)
{
    bool    enemyDeleted = false;

    if (map[y_pos][x_pos + 1] > 50) // CHECK RIGHT
    {
        this->currentDeletedEnemy = map[y_pos][x_pos + 1];
        map[y_pos][x_pos + 1] = 0;
        enemyDeleted = true;
    }
    if (map[y_pos][x_pos - 1] > 50) // CHECK LEFT
    {
        this->currentDeletedEnemy = map[y_pos][x_pos - 1];
        map[y_pos][x_pos - 1] = 0;
        enemyDeleted = true;
    }
    if (map[y_pos - 1][x_pos] > 50) // CHECK UP
    {
        this->currentDeletedEnemy = map[y_pos - 1][x_pos];
        map[y_pos - 1][x_pos] = 0;
        enemyDeleted = true;
    }
    if (map[y_pos + 1][x_pos] > 50) // CHECK DOWN
    {
        this->currentDeletedEnemy = map[y_pos + 1][x_pos];
        map[y_pos + 1][x_pos] = 0;
        enemyDeleted = true;
    }
    return (enemyDeleted);
}

void    GraphicsEngine::modelProjectionConfig()
{
    /*For projection*/
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    //getting uniform locations
    unsigned modelLoc, projectionLoc;

    projectionLoc = glGetUniformLocation(this->ourShader.ID, "projection");
    modelLoc = glGetUniformLocation(this->ourShader.ID, "model");

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //my attempt at rotation
    glm::mat4 trans = glm::mat4(1.0f);

    unsigned int transformLoc = glGetUniformLocation(this->ourShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    //activate shader
    this->ourShader.use();
    this->ourShader.setMat4("projection", projection);
}

void    GraphicsEngine::callMovementFunctions(Player &player, Sound &sound, Keys &keys, std::vector<std::vector<int> >  mapOfObjects)
{
    //camera movement functions
    this->cam.setCam(this->ourShader);
    this->cam.camMovements(keys);
    this->cam.camRotation(this->window);

    //Player movement control function
    if (player.playerMovements(this->window, sound, keys, mapOfObjects, this->player_direction) == 1)
        this->cam.playerCamMovements(keys);
}

void    GraphicsEngine::reset_camera()
{
    this->cam.cameraPos = glm::vec3(0.0f, 0.0f, 18.0f);
    this->cam.cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cam.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

std::vector<std::vector<int>>  GraphicsEngine::getCurrentObjectsMap()
{
	MapEngine m_engine;
	std::vector<std::vector<std::vector<int>>> maps = m_engine.getObjectsMaps();
  return (maps[this->currentMap]);
}

void    GraphicsEngine::updateMap(Player player, std::vector<std::vector<int> > & map)
{
    std::vector<int>  newPlayerPos = player.getNewPlayerPos();
    std::vector<int>  OldPlayerPos = player.getPrevPlayer();
    float curXplayerPos = player.getXcoord();
    float curYplayerPos = player.getYcoord();

    int   p_pos_x = 0;
    int   p_pos_y = 0;
    int   old_p_x = 0;
    int   old_p_y = 0;

    if (newPlayerPos.size())
    {
        //New Player Position
        p_pos_x = newPlayerPos[0];
        p_pos_y = newPlayerPos[1];

        //Old Player Position
        old_p_x = OldPlayerPos[0];
        old_p_y = OldPlayerPos[1];

        if (curXplayerPos >= nextXPos) 
        {
            prevXpos = curXplayerPos - 1.4f;
            nextXPos += 1.4f;
            map[old_p_y][old_p_x] = FLOOR;
            map[p_pos_y][p_pos_x] = PLAYER_OBJ;
        }
        else if (curYplayerPos >= nextYPos)
        {
            prevYpos = curYplayerPos - 1.3f;
            nextYPos += 1.3f;
            map[old_p_y][old_p_x] = FLOOR;
            map[p_pos_y][p_pos_x] = PLAYER_OBJ;
        }
        else if (curXplayerPos <= prevXpos)
        {
            nextXPos = curXplayerPos + 1.4f;
            prevXpos -= 1.4f;
            map[old_p_y][old_p_x] = FLOOR;
            map[p_pos_y][p_pos_x] = PLAYER_OBJ;
        }
        else if (curYplayerPos <= prevYpos)
        {
            nextYPos = curYplayerPos + 1.3f;
            prevYpos -= 1.3f;
            map[old_p_y][old_p_x] = FLOOR;
            map[p_pos_y][p_pos_x] = PLAYER_OBJ;
        }
        //   exit(0);
    }
}

bool    GraphicsEngine::array_check(std::vector<std::vector<int> > & map)
{
    int player_found = 0;

    // I = Y axis
    // J = X axis

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 3)
            {
                //Check the direction the player is facing
                //is BOMB placeable there
                //update map where nextpos = 0 put 4
                if (this->player_direction == 4) //RIGHT DIRECTION
                {
                    if (map[i][j + 1] == 0)
                    {
                        //placeBomb by updating map 0 becomes 4
                        if (map[i][j - 1] != FLOOR)
                            return (false);
                        else
                        {
                            map[i][j + 1] = BOMB;
                            return (true);
                        }
                    }
                    player_found = 1;
                    break;
                }
                else if (this->player_direction == 3) //LEFT DIRECTION
                {
                    if (map[i][j - 1] == FLOOR)
                    {
                        //placeBomb by updating map 0 becomes 4
                        if (map[i][j + 1] != FLOOR)
                            return (false);
                        else
                        {
                            map[i][j - 1] = BOMB;
                            return (true);
                        }
                    }
                    player_found = 1;
                    break;
                }
                else if (this->player_direction == 2) //DOWN DIRECTION
                {
                    if (map[i + 1][j] == FLOOR)
                    {
                        //placeBomb by updating map 0 becomes 4
                        if (map[i - 1][j] != FLOOR)
                            return (false);
                        else
                        {
                            map[i + 1][j] = BOMB;
                            return (true);
                        }                    
                    }
                    player_found = 1;
                    break;
                }
                else if (this->player_direction == 1) //UP DIRECTION
                {
                    if (map[i - 1][j] == FLOOR)
                    {
                        //placeBomb by updating map 0 becomes 4
                        if (map[i + 1][j] != FLOOR)
                            return (false);
                        else
                        {
                            map[i - 1][j] = BOMB;
                            return (true);
                        }
                    }
                    player_found = 1;
                    break;
                }
                // player_found = 1;
                // break;
            }
        }
        if (player_found == 1)
            break;
    }
    return (false);
}

bool    GraphicsEngine::createEnemyArray(std::vector<std::vector<int> >  map, unsigned int numCheck)
{
    int e_number = 53;
    std::vector<int>    enemyElements;

    for (unsigned int check = 0; numCheck > check; check++)
    {
        for (unsigned int i = 0; i < map.size(); i++)
        {
            for (unsigned int j = 0; j < map[i].size(); j++)
            {
                // std::cout << "mapOfObjects: 2: " << mapOfObjects[i].size() << std::endl;    
                if (map[i][j] == e_number)
                {
                    enemyElements.clear();
                    enemyElements.push_back(e_number);
                    enemyElements.push_back(j); //Enemy X coord on the map of objects   
                    enemyElements.push_back(i); //Enemy Y coord on the map of objects
                    this->enemyNumbers.push_back(enemyElements);
                }
            }
        }
        e_number++;
    }

    if (this->enemyNumbers.size() >= 1)
    {
        std::sort(enemyNumbers.begin(), enemyNumbers.end());
        return (true);
    }
    return (false);
}

void    GraphicsEngine::remove_bomb(std::vector<std::vector<int> > & map)
{
    // int bomb_found = 0;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            // std::cout << "mapOfObjects: 2: " << mapOfObjects[i].size() << std::endl;    
            if (map[i][j] == BOMB)
            {
                map[i][j] = FLOOR;
                // bomb_found = 1;
            }
        }
    }
}

void    GraphicsEngine::remove_life(std::vector<std::vector<int> > & map)
{
    int player_life_found = 0;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            // std::cout << "mapOfObjects: 2: " << mapOfObjects[i].size() << std::endl;    
            if (map[i][j] == 8)
            {
                map[i][j] = FLOOR;
                player_life_found = 1;
                break;
            }
        }
        if (player_life_found == 1)
            break;
    }
}

void    GraphicsEngine::reset_player_location(std::vector<std::vector<int> > & map)
{
    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            // std::cout << "mapOfObjects: 2: " << mapOfObjects[i].size() << std::endl;    
            if (map[i][j] == PLAYER_OBJ)
            {
                map[i][j] = FLOOR;
            }
        }
    }
}


int    GraphicsEngine::update_bomb_range(std::vector<std::vector<int> > & map)
{
    // 3 = PLAYER FOUND IN THE BOMB RANGE
    // 2 = ENEMY FOUND IN THE BOMB RANGE
    // 1 = NOTHING FOUND IN THE BOMB RANGE

    int bomb_found = 0;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            // std::cout << "mapOfObjects: 2: " << mapOfObjects[i].size() << std::endl;    
            if (map[i][j] == 4)
            {
                //SETTING BOMB COORDINATES
                this->bombXCoord = j;
                this->bombYCoord = i;

                //INCREASING BOMB RANGE
                if (map[i][j + 1] == 0 || map[i][j + 1] == 3 || map[i][j + 1] >= 50 || map[i][j + 1] == DOOR || map[i][j + 1] == 2) //Updating right
                {
                    if (map[i][j + 1] == 0 || map[i][j + 1] == 2)
                        map[i][j + 1] = 4;
                    if (map[i][j + 1] == 3)
                        return (3);
                    if (map[i][j + 1] == 5)
                        return (2);
                    if  (map[i][j + 1] >= 50)
                    {
                        this->deleteEnemy = true;
                        return (10);
                    }
                    if (map[i][j + 1] == DOOR)
                        this->isDoor = true;
                }
                if (map[i][j - 1] == 0 || map[i][j - 1] == 3 || map[i][j - 1] >= 50|| map[i][j - 1] == DOOR || map[i][j - 1] == 2) // Updating left
                {
                    if (map[i][j - 1] == 0 || map[i][j - 1] == 2)
                        map[i][j - 1] = 4;
                    if (map[i][j - 1] == 3)
                        return (3);
                    if (map[i][j - 1] == 5)
                        return (2);
                    if (map[i][j - 1] >= 50)
                    {
                        this->deleteEnemy = true;
                        return (10);
                    }
                    if (map[i][j - 1] == DOOR)
                        this->isDoor = true;
                }
                if (map[i + 1][j] == 0 || map[i + 1][j] == 3 || map[i + 1][j] >= 50 || map[i + 1][j] == DOOR || map[i + 1][j] == 2) //Updating down
                {
                    if (map[i + 1][j] == 0 || map[i + 1][j] == 2)
                        map[i + 1][j] = 4;
                    if (map[i + 1][j] == 3)
                        return (3);
                    if (map[i + 1][j] == 5)
                        return (2);
                    if (map[i + 1][j] >= 50)
                    {
                        this->deleteEnemy = true;
                        return (10);
                    }
                    if (map[i + 1][j] == DOOR)
                        this->isDoor = true;
                }
                if (map[i - 1][j] == 0 || map[i - 1][j] == 3 || map[i - 1][j] >= 50 || map[i - 1][j] == DOOR || map[i - 1][j] == 2) //Updating up
                {
                    if (map[i - 1][j] == 0 || map[i - 1][j] == 2)
                        map[i - 1][j] = 4;
                    if (map[i - 1][j] == 3)
                        return (3);
                    if (map[i - 1][j] == 5)
                        return (2);
                    if (map[i - 1][j] >= 50)
                    {
                        this->deleteEnemy = true;
                        return (10);
                    }
                    if (map[i - 1][j] == DOOR)
                        this->isDoor = true;
                }
                bomb_found = 1;
                break;
            }
        }
        if (bomb_found == 1)
            break;
    }
    return (-1);
}

bool processInput(Keys &keys)
{
    if (keys.input() ==  EXIT)
        return true;
	return false;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}