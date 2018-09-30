/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsEngine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:29:25 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/30 10:33:09 by amatshiy         ###   ########.fr       */
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
    Player  player;
    Model_Objects   model_object;

    //Physics Engine
    PhysicsEngine p_engine;

    //MapEngine Testing
    MapEngine m_engine;
    m_engine.getMapPaths("./maps");
    m_engine.convertMaps();
    std::vector<std::vector<std::vector<int>>> maps = m_engine.getObjectsMaps();

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
            if (maps[this->currentMap][j][i] == 1)
            {
                std::cout << maps[this->currentMap][j][i] << " ";
                model_object.hard_wall_func(this->ourShader, this->pos_x, this->pos_y);
            }
            if (maps[this->currentMap][j][i] == 2)
            {
                std::cout << maps[this->currentMap][j][i] << " ";
                model_object.soft_wall_func(this->ourShader, this->pos_x, this->pos_y);
            }
            if (maps[this->currentMap][j][i] == 0)
            {
                std::cout << maps[this->currentMap][j][i] << " ";
                //TODO
            }if (maps[this->currentMap][j][i] == 3)
            {
                std::cout << maps[this->currentMap][j][i] << " ";
                //TODO
            }
            player.bodyModel(this->ourShader);
            player.headModel(this->ourShader);
            this->pos_x += 1.4f;

            }
            std::cout << std::endl;
            this->pos_y += 1.3f;
            this->pos_x = 0.0f;
        }
        this->pos_y = 0.0f;

        glfwSwapBuffers(this->window);
        glfwPollEvents();

        this->callMovementFunctions(player, sound, keys, maps[this->currentMap]);
        this->updateMap(player, maps[this->currentMap]);
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
    cam.setCam(this->ourShader);
    cam.camMovements(keys);
    cam.camRotation(this->window);

    //Player movement control function
    if (player.playerMovements(this->window, sound, keys, mapOfObjects) == 1)
        cam.playerCamMovements(keys);
}

void    GraphicsEngine::dumpArray()
{
  MapEngine m_engine;

  std::vector<std::vector<std::vector<int> > > maps = m_engine.getObjectsMaps();

  std::cout << "Array of Objects:" << std::endl;
  for (unsigned int i = 0; i < maps[this->currentMap].size(); i++)
  {
    for (unsigned int j = 0; maps[this->currentMap][i].size(); j++)
    {
      std::cout << maps[this->currentMap][i][j] << " ";
    }
    std::cout << std::endl;
  }
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

    // std::cout << "Player X coord: " << player.getXcoord() << std::endl;
    // std::cout << "Player Y coord: " << player.getYcoord() << std::endl;

    // std::cout << "State Result X: " << (curXplayerPos >= nextXPos) << std::endl;
    // std::cout << "State Result Y: " << (curYplayerPos >= nextYPos) << std::endl;
    // std::cout << "Static X Var: " << nextXPos << std::endl;
    // std::cout << "Static Y Var: " << nextYPos << std::endl;

    if (newPlayerPos.size())
    {
        //New Player Position
        p_pos_x = newPlayerPos[0];
        p_pos_y = newPlayerPos[1];

        //Old Player Position
        old_p_x = OldPlayerPos[0];
        old_p_y = OldPlayerPos[1];
        //   std::cout << "MainControl: p_pos_x: " << p_pos_x << std::endl;
        //   std::cout << "MainControl: p_pos_y: " << p_pos_y << std::endl;

        //   std::cout << "MainControl: old_p_pos_x: " << old_p_x << std::endl;
        //   std::cout << "MainControl: old_p_pos_x: " << old_p_y << std::endl;

        if (curXplayerPos >= nextXPos) // || (curYplayerPos >= nextXPos)
        {
            prevXpos = curXplayerPos - 1.4f;
            nextXPos += 1.4f;
            map[old_p_y][old_p_x] = 0;
            map[p_pos_y][p_pos_x] = 3;
        }
        else if (curYplayerPos >= nextYPos)
        {
            prevYpos = curYplayerPos - 1.3f;
            nextYPos += 1.3f;
            map[old_p_y][old_p_x] = 0;
            map[p_pos_y][p_pos_x] = 3;
        }
        else if (curXplayerPos <= prevXpos)
        {
            nextXPos = curXplayerPos + 1.4f;
            prevXpos -= 1.4f;
            map[old_p_y][old_p_x] = 0;
            map[p_pos_y][p_pos_x] = 3;
        }
        else if (curYplayerPos <= prevYpos)
        {
            nextYPos = curYplayerPos + 1.3f;
            prevYpos -= 1.3f;
            map[old_p_y][old_p_x] = 0;
            map[p_pos_y][p_pos_x] = 3;
        }
        //   exit(0);
    }
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
