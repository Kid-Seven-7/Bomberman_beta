/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsEngine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:29:25 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 18:46:57 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine(){
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

GraphicsEngine::GraphicsEngine(GLFWwindow  *window){
	this->window = window;
	this->gladConfg();

	//Variable Init
	this->ourShader = Shader("Shaders/texture.vs", "Shaders/texture.fs");
	glEnable(GL_DEPTH_TEST);

	//Initializing current map
	this->currentMap = 0;
}

GraphicsEngine::~GraphicsEngine(){
    glfwTerminate();
}

void    GraphicsEngine::glfwConfig(){
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

void    GraphicsEngine::gladConfg(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

void    GraphicsEngine::MainControl(Sound &sound, Keys &keys){
    Player  player;
    Model_Objects   model_object;

    //Physics Engine
    PhysicsEngine p_engine;

    //MapEngine Testing
    MapEngine m_engine;
    m_engine.getMapPaths("./maps");
    m_engine.convertMaps();
    std::vector<std::vector<std::vector<int>>> maps = m_engine.getObjectsMaps();
    unsigned int optimizeArray = 0;
		// int menu = 0;

    while (!glfwWindowShouldClose(this->window)){
      //input process
      if (processInput(keys)){
				// menu++;
				// glBindVertexArray(0);
				// break;
				m_engine.dumpCurrentMap(this->currentMap);
				std::ofstream file("gameState/playerCoords.pcs");
				file << player.getXcoord() << ":" << player.getYcoord() << std::endl;
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

      for (unsigned int j = 0; j < maps[this->currentMap].size(); j++){
        for (unsigned int i = 0; i < maps[this->currentMap][j].size(); i++){
          if (maps[this->currentMap][j][i] == 1){
            model_object.hard_wall_func(this->ourShader, this->pos_x, this->pos_y);
            if (optimizeArray < maps[this->currentMap].size()){
              this->xy_coords.push_back(this->pos_x);
              this->xy_coords.push_back(this->pos_y);
            }
          }
          if (maps[this->currentMap][j][i] == 2){
            model_object.soft_wall_func(this->ourShader, this->pos_x, this->pos_y);
            this->xy_coords.push_back(this->pos_x);
            this->xy_coords.push_back(this->pos_y);
          }
          if (maps[this->currentMap][j][i] == 0){
            if (optimizeArray < maps[this->currentMap].size()){
              this->xy_coords.push_back(this->pos_x);
              this->xy_coords.push_back(this->pos_y);
            }
          }
          player.bodyModel(this->ourShader);
          player.headModel(this->ourShader);
          this->pos_x += 1.3f;

          //Adding to the larger array
          this->array_of_xy.push_back(this->xy_coords);
          this->xy_coords.clear();
        }
        this->pos_y += 1.3f;
        this->pos_x = 0.0f;

        this->map_of_coords.push_back(this->array_of_xy);
        this->array_of_xy.clear();


        //Array optimazation
        if (optimizeArray < maps[this->currentMap].size())
            optimizeArray++;
      }
      this->pos_y = 0.0f;

      glfwSwapBuffers(this->window);
      glfwPollEvents();

      this->callMovementFunctions(player, sound, keys);
    }
		// if (menu != 0){
		// 	m_engine.dumpCurrentMap(this->currentMap);
		// 	std::ofstream file("gameState/playerCoords.pcs");
		// 	file << player.getXcoord() << ":" << player.getYcoord() << std::endl;
		// 	displayStart(sound, keys, window);
		// }

}

void    GraphicsEngine::modelProjectionConfig(){
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

void    GraphicsEngine::callMovementFunctions(Player &player, Sound &sound, Keys &keys){
    //camera movement functions
    cam.setCam(this->ourShader);
    cam.camMovements(keys);
    cam.camRotation(this->window);
    cam.playerCamMovements(keys);

    //Player movement control function
    player.playerMovements(this->window, sound, keys);
}

std::vector<std::vector<std::vector<float>>>  GraphicsEngine::getCoordsMap(){
    return (this->map_of_coords);
}

void    GraphicsEngine::dumpArray(){
  for (size_t i = 0; i < this->map_of_coords[0].size(); i++){
    for (size_t j = 0; j < this->map_of_coords[i].size(); j++){
      for (size_t k = 0; k < this->map_of_coords[i][j].size(); k++){
        std::cout << this->map_of_coords[i][j][k] << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "Array X size: " << this->map_of_coords.size() << std::endl;
  std::cout << "Array Y size: " << this->map_of_coords[0].size() << std::endl;
}

std::vector<std::vector<int>>  GraphicsEngine::getCurrentObjectsMap()
{
	MapEngine m_engine;
	std::vector<std::vector<std::vector<int>>> maps = m_engine.getObjectsMaps();
  return (maps[this->currentMap]);
}

bool processInput(Keys &keys){
    if (keys.input() ==  EXIT)
        return true;
		return false;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    (void)window;
    glViewport(0, 0, width, height);
}
