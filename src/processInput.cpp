/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/bomberman.hpp"
# include "../Image_Loader/image_loader.hpp"

void readFile(std::string filepath){
	std::string line, playerInfo, camInfo, mapInfo;
	int index = 1;

  std::ifstream saveFile(filepath);
  if (saveFile.is_open()){
    while (getline (saveFile,line)){
			line += "\n";
			if (index > 0 && index < 3)
				playerInfo += line;
			if (index > 3 && index < 18)
				camInfo += line;
			if (index > 18)
				mapInfo += line;
			index++;
		}
    saveFile.close();
  }
  else
		std::cout << "Unable to open file";

	std::cout << "playerInfo :\n" << playerInfo << '\n';
	std::cout << "camInfo :\n" << camInfo << '\n';
	std::cout << "mapInfo :\n" << mapInfo << '\n';
}

void noSaveFile(unsigned int *texture, unsigned int *menu, float *vert){
	*vert = 10.0f;
	*texture = setTexture(texture, "bomberman_assets/wallpapers/nosave.jpg");
	*menu = NO_SAVE_FILE;
}

bool saveGameState(std::string path){
	if (does_file_exist("gameState/playerCoords.txt") &&
			does_file_exist("gameState/camInfo.txt") &&
			does_file_exist("gameState/mapstate.txt")){

		std::ofstream output(path);
		std::ifstream player("gameState/playerCoords.txt");
		std::ifstream map("gameState/camInfo.txt");
		std::ifstream cam("gameState/mapstate.txt");

		output << player.rdbuf() << '\n';
		output << map.rdbuf() << '\n';
		output << cam.rdbuf() << '\n';

		if (does_file_exist(path))
			return true;
		else
		std::cout << "failed to save" << '\n';
	}else{
		std::cout << "save files missing" << '\n';
	}

	return false;
}

/*
	Parameters:
		std::string filepath- Path to save file to be opened
	Return:
		void
	Synopsis:
		Determines if a save file exists or not
*/
void loadFile(std::string filepath, unsigned int *texture, unsigned int *menu, float *vert){
	if (does_file_exist(filepath))
		// std::cout << "file exists" << '\n';
		readFile(filepath);
	else
		noSaveFile(texture, menu, vert);
}

/*
	Parameters:
		int slot- The selected slot number
	Return:
		void
	Synopsis:
		Creates a save file
*/
int saveFile(int slot){
	int error = 0;
	if (slot == 1){
		if (!saveGameState("save/slot1.txt"))
			error = 1;
	}else if (slot == 2){
		if (!saveGameState("save/slot2.txt"))
			error = 1;
	}else if (slot == 3){
		if (!saveGameState("save/slot3.txt"))
			error = 1;
	}else if (slot == 4){
		if (!saveGameState("save/slot4.txt"))
			error = 1;
	}else if (slot == 5){
		if (!saveGameState("save/slot5.txt"))
			error = 1;
	}
	return (error);
}

/*
	Parameters:
		std::string fileName- The path to the file to validate
	Return:
		bool- true if file exists else false
	Synopsis:
		Validates if a file exists
*/
bool does_file_exist(std::string fileName){
    std::ifstream infile(fileName);
    return infile.good();
}

void displayStart(Sound &sound, Keys &keys, GLFWwindow* window){
	// build and compile our shader zprogram
	Shader ourShader("Shaders/textureVert.shader", "Shaders/textureFrag.shader");
  Shader myShader("Shaders/vert.shader", "Shaders/frag.shader");
	unsigned int texture = setTexture(0, "bomberman_assets/wallpapers/menu.jpg");

  // set up vertex data (and buffer(s)) and configure vertex attributes
  float vertices[] = {
    // positions          // colors           // texture coords
     0.9f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.9f, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.9f,  0.9f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
  };

	float s_vertices[] = {
		//positions
		-0.6f,  0.2f, 0.0f,  // top right
		-0.6f, -0.1f, 0.0f,  // bottom right
		-0.65f, -0.1f, 0.0f,  // bottom left
		-0.65f,  0.2f, 0.0f   // top left
	};

  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

	unsigned int VBO, VAO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

	unsigned int VBO1, VAO1, EBO1;

	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &EBO1);

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertices), s_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);

	glDisable(GL_DEPTH_TEST);
  // render loop
  while (!glfwWindowShouldClose(window)){
    // input

    if (processInput(window, myShader, sound, &texture, keys))
			return;

    // render
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind Texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // render container
    ourShader.use();
		glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		myShader.use();
		glBindVertexArray(VAO1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
  glDeleteVertexArrays(1, &VAO1);
  glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO1);
  glDeleteBuffers(1, &EBO);
  glDeleteBuffers(1, &EBO1);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
}

/*
	Parameters:
		GLFWwindow *window- GLFW window instance
		Shader myShader- Shader class
		Sound &sound- Reference to sound class
		unsigned int *texture- pointer to texture array
		Keys &keys- Reference to keys class
	Return:
		void
	Synopsis:
		A game menu
*/
bool processInput(GLFWwindow *window, Shader myShader, Sound &sound, unsigned int *texture, Keys &keys)
{
	static unsigned char i = 0;
	static unsigned int menu = MAIN;
	static int keyType = ARROW;
	static float vert, hori = 0.0f;
	int vertexPosLocation = glGetUniformLocation(myShader.ID, "newPosition");

	glUniform4f(vertexPosLocation, hori, vert, 0.2f, 1.0f);

	if (++i % 4 == 0){
		if (menu == MAIN && vert == 0.7f){
			if (keys.input() == ENTER){
				if (does_file_exist("gameState/mapstate.txt"))
					return true;
				gameplay(window, sound, keys);
			}
		}
		if (menu == KEYMAPPING){
			vert = -10.0f;
			if (keys.input() == RIGHT){
				sound.playFX(SWIPE);
				keyType += (keyType < 202)?1:0;
			}
			else if (keys.input() == LEFT){
				sound.playFX(SWIPE);
				keyType -= (keyType > 200)?1:0;
			}
			else if (keys.input() == ENTER){
				keys.setKeys(keyType);
			}
			*texture = (keyType == 202) ? setTexture(texture, "bomberman_assets/wallpapers/numpadkeys.jpg") :
				(keyType == 201) ? setTexture(texture, "bomberman_assets/wallpapers/wasdkeys.jpg") :
				setTexture(texture, "bomberman_assets/wallpapers/arrowkeys.jpg") ;
		}
		if (keys.input() == UP && menu != KEYMAPPING){
			sound.playFX(SWIPE);
			if (menu == VOLUME)
				vert += (vert < 0.35f)?0.35f:0.0f;
			else if (menu == CHEATS)
				vert = (vert == -0.35f)?0.35f:-0.35f;
			else
				vert += (vert < 0.7f)?0.35f:0.0f;
		}
		else if (keys.input() == DOWN && menu != KEYMAPPING){
			sound.playFX(SWIPE);
			if (menu == VOLUME)
				vert -= (vert > -0.35f)?0.35f:0.0f;
			else if (menu == CHEATS)
				vert = (vert == 0.35f)?-0.35f:0.35f;
			else
				vert -= (vert > -0.7f)?0.35f:0.0f;
		}
		else if (keys.input() == ENTER){
			sound.playFX(BASS);
			switch (menu){
				case MAIN:
					if (vert == 0.35f){
						*texture = setTexture(texture, "bomberman_assets/wallpapers/save.jpg");
						menu = SAVE;
					}
					else if (vert == 0.0f){
						*texture = setTexture(texture, "bomberman_assets/wallpapers/save.jpg");
						menu = LOAD;
					}
					else if (vert == -0.7f){
						*texture = setTexture(texture, "bomberman_assets/wallpapers/settings.jpg");
						menu = SETTINGS;
					}
					else if (vert == -0.35f){
						if (does_file_exist("gameState/mapstate.txt"))
							remove("gameState/mapstate.txt");
						if (does_file_exist("gameState/playerCoords.txt"))
							remove("gameState/playerCoords.txt");
						if (does_file_exist("gameState/camInfo.txt"))
							remove("gameState/camInfo.txt");
						exit(0);
					}
					break;
				case SAVE:
					if(vert == 0.7f){
						if (saveFile(1))
							noSaveFile(texture, &menu, & vert);
					}
					else if(vert == 0.35f){
						if (saveFile(2))
							noSaveFile(texture, &menu, & vert);
					}
					else if(vert == 0.0f){
						if (saveFile(3))
							noSaveFile(texture, &menu, & vert);
					}
					else if(vert == -0.35f){
						if (saveFile(4))
							noSaveFile(texture, &menu, & vert);
					}
					else if(vert == -0.7f){
						if (saveFile(5))
							noSaveFile(texture, &menu, & vert);
					}
					break;
				case LOAD:
					if(vert == 0.7f)
						loadFile("save/slot1.txt", texture, &menu, &vert);
					else if(vert == 0.35f)
						loadFile("save/slot2.txt", texture, &menu, &vert);
					else if(vert == 0.0f)
						loadFile("save/slot3.txt", texture, &menu, &vert);
					else if(vert == -0.35f)
						loadFile("save/slot4.txt", texture, &menu, &vert);
					else if(vert == -0.7f)
						loadFile("save/slot5.txt", texture, &menu, &vert);
					break;
				case SETTINGS:
					if (vert == 0.7f){
						*texture = setTexture(texture, "bomberman_assets/wallpapers/sound.jpg");
						menu = VOLUME;
						vert = 0.0f;
					}
					else if (vert == 0.35f){
						*texture = setTexture(texture, "bomberman_assets/wallpapers/arrowkeys.jpg");
						menu = KEYMAPPING;
					}
					else if (vert == 0.0f){
						*texture = setTexture(texture, "bomberman_assets/wallpapers/reso.jpg");
						menu = RESOLUTION;
					}
					else if (vert == -0.35f){
						vert = 0.35f;
						*texture = setTexture(texture, "bomberman_assets/wallpapers/screenMode.jpg");
						menu = CHEATS;
					}
					else if (vert == -0.7f){
						vert = -10.0f;
						*texture = setTexture(texture, "bomberman_assets/wallpapers/credits.jpg");
						menu = CREDITS;
					}
					break;
					case CHEATS:
						if (vert == 0.35f){
							glfwTerminate();

							if (!glfwInit()){
					        std::cout << "GLFW failed to start" << std::endl;
					        exit(1);
					    }

							glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
					    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
					    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
					    #ifdef __APPLE__
					        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
					    #endif

					    window = glfwCreateWindow(1280, 800, "Bomberman 42", NULL, NULL);

					    if (!window){
					        std::cout << "Failed to create window" << std::endl;
					        glfwTerminate();
					        exit(-1);
					    }

					    //Making the window the current context
					    glfwMakeContextCurrent(window);
							initCheck();
					    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //For screen resolution
							keys.setWindow(window);
							menu = MAIN;
							displayStart(sound, keys, window);
						}
						else if (vert == -0.35f){
							const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
							glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
						}
						break;
				case RESOLUTION:
					if (vert == 0.7f)
						glfwSetWindowSize(window, 1366, 768);
					else if (vert == 0.35f)
						glfwSetWindowSize(window, 1920, 1080);
					else if (vert == 0.0f)
						glfwSetWindowSize(window, 1280, 800);
					else if (vert == -0.35f)
						glfwSetWindowSize(window, 1600, 900);
					else if (vert == -0.7f)
						glfwSetWindowSize(window, 1280, 720);
					break;
			}
		}
		else if (keys.input() == ACTION)
			sound.playFX(GHOST);
		else if (keys.input() == NEXT)
			sound.nextLoop();
		else if (keys.input() == PREV)
			sound.prevLoop();
		else if (keys.input() == RIGHT && menu == VOLUME){
			if(vert == 0.35f){
				sound.setVolumeLevel("SFX", 10.0f);
				sound.setVolumeLevel("LOOP", 10.0f);
			}else if(vert == 0.0f)
				sound.setVolumeLevel("LOOP", 10.0f);
			else if(vert == -0.35f)
				sound.setVolumeLevel("SFX", 10.0f);
		}
		else if (keys.input() == LEFT && menu == VOLUME){
			if(vert == 0.35f){
				sound.setVolumeLevel("SFX", -10.0f);
				sound.setVolumeLevel("LOOP", -10.0f);
			}else if(vert == 0.0f)
				sound.setVolumeLevel("LOOP", -10.0f);
			else if(vert == -0.35f)
				sound.setVolumeLevel("SFX", -10.0f);
		}
	}
	if (keys.input() == EXIT){
		vert = 0.0f;
		if (menu == RESOLUTION || menu == VOLUME){
			*texture = setTexture(texture, "bomberman_assets/wallpapers/settings.jpg");
			menu = SETTINGS;
		}
		else{
			*texture = setTexture(texture, "bomberman_assets/wallpapers/menu.jpg");
			menu = MAIN;
		}
	}
	return false;
}

/*
	Parameters:
		std::string file- The path of the image to be loaded
	Return:
		unsigned int texture- An array storing the loaded texture
	Synopsis:
		Generates, binds and configure a texture and loads an array of said texture
		into an unsigned int array
*/
unsigned int setTexture(unsigned int *old_texture, std::string file){
	// load and create a texture
	if (old_texture)
		glDeleteTextures(1, old_texture);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	ImageLoader loader(file, width, height, nrChannels);

	unsigned char *data = loader.getImageData();

	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else
		std::cout << "Failed to load texture" << std::endl;

	return (texture);
}
