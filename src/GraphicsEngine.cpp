/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsEngine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:29:25 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/19 12:08:46 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine()
{
    if (!glfwInit()){
        std::cout << "GLFW failed to start" << std::endl;
        exit(1);
    }
    this->glfwConfig();
    this->gladConfg();

    //Variable Init
    this->ourShader = Shader("Shaders/texture.vs", "Shaders/texture.fs");
    glEnable(GL_DEPTH_TEST);

    //Initializing current map
    this->currentMap = 0;

    //Default player direction
     this->player_direction = -1;
     this->lives = 2;
     this->cam = CameraClass();
}

GraphicsEngine::GraphicsEngine(GLFWwindow  *window)
{
	this->window = window;
	this->gladConfg();

	//Variable Init
	this->ourShader = Shader("Shaders/texture.vs", "Shaders/texture.fs");
	glEnable(GL_DEPTH_TEST);

	//Initializing current map
	this->currentMap = 0;

    //Default player direction
     this->player_direction = -1;
     this->lives = 2;
     this->cam = CameraClass();
}

GraphicsEngine::~GraphicsEngine()
{
    glfwTerminate();
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

void    GraphicsEngine::MainControl(Sound &sound, Keys &keys)
{
    Player          player;
    Model_Objects   model_object;
    BombClass       bomb;
    int             bomb_counter = 0;
    int             pause_counter = 60;
    bool            start_counter = false;
    bool            reset_player = false;

    //Physics Engine
    // PhysicsEngine p_engine; // remove this ENGINE BEFORE SUBMISSION

    //MapEngine Testing
    MapEngine m_engine;
    m_engine.getMapPaths("./maps");
    m_engine.convertMaps();

    
    std::vector<std::vector<std::vector<int>>> maps = m_engine.getObjectsMaps();



    if (this->createEnemyArray(maps[this->currentMap], 3))
    {
        //create enemies
        system("say enemies");
        std::cout << "Number of Enemies: " << this->enemyNumbers.size() << std::endl;
        std::cout << "Found Enemy: " << this->enemyNumbers[0] << std::endl;
        std::cout << "Found Enemy: " << this->enemyNumbers[1] << std::endl;

        for (unsigned int x = 0; x < this->enemyNumbers.size(); x++)
        {
            Enemy enemy = Enemy(this->enemyNumbers[x], ourShader, this->currentMap + 1);
            this->enemies.push_back(enemy);
        }
    }
    exit(0);

    while (!glfwWindowShouldClose(this->window))
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

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Start of rendering...
        this->modelProjectionConfig();
        model_object.universe_func(ourShader);
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
                    std::cout << maps[this->currentMap][j][i] << " ";
                    model_object.hard_wall_func(this->ourShader, this->pos_x, this->pos_y);
                }
                if (maps[this->currentMap][j][i] == SOFT_WALL)
                {
                    // std::cout << this->pos_x << " " << this->pos_y << " ";
                    std::cout << maps[this->currentMap][j][i] << " ";
                    model_object.soft_wall_func(this->ourShader, this->pos_x, this->pos_y);
                }
                if (maps[this->currentMap][j][i] == FLOOR)
                {
                    // std::cout << this->pos_x << " " << this->pos_y << " ";
                    std::cout << maps[this->currentMap][j][i] << " ";
                    //TODO
                }
                if (maps[this->currentMap][j][i] == PLAYER_OBJ)
                {
                    // std::cout << this->pos_x << " " << this->pos_y << " ";
                    std::cout << maps[this->currentMap][j][i] << " ";
                    //TODO
                }
                if (maps[this->currentMap][j][i] == 8)
                {
                    // std::cout << this->pos_x << " " << this->pos_y << " ";
                    std::cout << maps[this->currentMap][j][i] << " ";
                    model_object.player_life_func(this->ourShader, this->pos_x, this->pos_y);
                    model_object.headModel(this->ourShader, this->pos_x, this->pos_y);
                    //TODO
                }
                if (maps[this->currentMap][j][i] == BOMB)
                {
                    // std::cout << this->pos_x << " " << this->pos_y << " ";
                    std::cout << maps[this->currentMap][j][i] << " ";
                    //FIX BOMB CLASS!!!
                    //CALL ARRAY CHECK BEFORE PLACING BOMB
                    bomb.putBomb(ourShader, this->pos_x, this->pos_y, 1);
                    if (bomb_counter >= 75)
                        bomb.putBomb(ourShader, this->pos_x, this->pos_y, 2);
                }
                if (maps[this->currentMap][j][i] == 54)
                {
                    std::cout << maps[this->currentMap][j][i] << " ";
                }
                player.bodyModel(this->ourShader);
                player.headModel(this->ourShader);
                this->pos_x += 1.4f;
            }
            // std::cout << "Player X: " << player.getXcoord() << std::endl;
            // std::cout << "Player Y: " << player.getYcoord() << std::endl;
            std::cout << std::endl;
            this->pos_y += 1.3f;
            this->pos_x = 0.0f;
        }
        this->pos_y = 0.0f;
        if (start_counter)
            bomb_counter++;
        if (bomb_counter == 75)
        {
            if (this->update_bomb_range(maps[this->currentMap]) == 3)
            {
                if (this->lives >= 1)
                {
                    this->remove_life(maps[this->currentMap]);
                    player.setPcoords(0.0f, 0.0f);
                    this->reset_player_location(maps[this->currentMap]);
                    this->reset_camera();
                    reset_player = true;
                }
            }
        }
        if (bomb_counter >= 150)
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

        glfwSwapBuffers(this->window);
        glfwPollEvents();

        if (keys.input() == SPACE)
        {
            if (!(start_counter) && (this->array_check(maps[this->currentMap])))
                start_counter = true;
        }
        if (pause_counter >= 60)
            this->callMovementFunctions(player, sound, keys, maps[this->currentMap]);
        this->updateMap(player, maps[this->currentMap]);
        m_engine.updateCurrentMap(currentMap, maps[this->currentMap]);
    }
    nextXPos = 2.6f;
    nextYPos = 2.6f;
    prevXpos = -2.6f;
    prevYpos = -2.6f;
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

    for (unsigned int check = 0; numCheck > check; check++)
    {
        for (unsigned int i = 0; i < map.size(); i++)
        {
            for (unsigned int j = 0; j < map[i].size(); j++)
            {
                // std::cout << "mapOfObjects: 2: " << mapOfObjects[i].size() << std::endl;    
                if (map[i][j] == e_number)
                {
                    std::cout << "Enemy: " << e_number << std::endl;
                    this->enemyNumbers.push_back(e_number);
                }
                // bomb_found = 1;
            }
        }
        e_number++;
    }

    if (this->enemyNumbers.size() >= 1)
        return (true);
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
    int player_found = 0;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            // std::cout << "mapOfObjects: 2: " << mapOfObjects[i].size() << std::endl;    
            if (map[i][j] == PLAYER_OBJ)
            {
                map[i][j] = FLOOR;
                map[1][1] = PLAYER_OBJ;
                player_found = 1;
                break;
            }
        }
        if (player_found == 1)
            break;
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
                //INCREASING BOMB RANGE
                if (map[i][j + 1] == 0 || map[i][j + 1] == 3 || map[i][j + 1] == 5 || map[i][j + 1] == 2) //Updating right
                {
                    if (map[i][j + 1] == 0 || map[i][j + 1] == 2)
                        map[i][j + 1] = 4;
                    if (map[i][j + 1] == 3)
                        return (3);
                    if (map[i][j + 1] == 5)
                        return (2);
                }
                if (map[i][j - 1] == 0 || map[i][j - 1] == 3 || map[i][j - 1] == 5 || map[i][j - 1] == 2) // Updating left
                {
                    if (map[i][j - 1] == 0 || map[i][j - 1] == 2)
                        map[i][j - 1] = 4;
                    if (map[i][j - 1] == 3)
                        return (3);
                    if (map[i][j - 1] == 5)
                        return (2);
                }
                if (map[i + 1][j] == 0 || map[i + 1][j] == 3 || map[i + 1][j] == 5 || map[i + 1][j] == 2) //Updating down
                {
                    if (map[i + 1][j] == 0 || map[i + 1][j] == 2)
                        map[i + 1][j] = 4;
                    if (map[i + 1][j] == 3)
                        return (3);
                    if (map[i + 1][j] == 5)
                        return (2);
                }
                if (map[i - 1][j] == 0 || map[i - 1][j] == 3 || map[i - 1][j] == 5 || map[i - 1][j] == 2) //Updating up
                {
                    if (map[i - 1][j] == 0 || map[i - 1][j] == 2)
                        map[i - 1][j] = 4;
                    if (map[i - 1][j] == 3)
                        return (3);
                    if (map[i - 1][j] == 5)
                        return (2);
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