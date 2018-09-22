/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/bomberman.hpp"

/*
	Parameters:
		std::string filepath- Path to save file to be opened
	Return:
		void
	Synopsis:
		Determines if a save file exists or not
*/
void loadFile(std::string filepath){
	if (does_file_exist(filepath))
		std::cout << "file exists" << '\n';
	else
		std::cout << "no such file" << '\n';
}

/*
	Parameters:
		int slot- The selected slot number
	Return:
		void
	Synopsis:
		Creates a save file
*/
void saveFile(int slot){
	if (slot == 1)
		system("touch save/slot1.svf");
	if (slot == 2)
		system("touch save/slot2.svf");
	if (slot == 3)
		system("touch save/slot3.svf");
	if (slot == 4)
		system("touch save/slot4.svf");
	if (slot == 5)
		system("touch save/slot5.svf");
	std::cout << "saved file" << '\n';
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
void processInput(GLFWwindow *window, Shader myShader, Sound &sound, unsigned int *texture, Keys &keys)
{
	(void)keys;
	static unsigned char i = 0;
	static unsigned int menu = MAIN;
	static int keyType = ARROW;
	static float vert, hori = 0.0f;
	int vertexPosLocation = glGetUniformLocation(myShader.ID, "newPosition");

	glUniform4f(vertexPosLocation, hori, vert, 0.2f, 1.0f);

	if (++i % 4 == 0){
		if (menu == KEYMAPPING){
			vert = -10.0f;
			if (keys.input() == RIGHT){
				sound.playFX(SWIPE);
				keyType += (keyType < 1)?1:0;
			}
			else if (keys.input() == LEFT){
				sound.playFX(SWIPE);
				keyType -= (keyType > -1)?1:0;
			}
			else if (keys.input() == ENTER){
				keys.setKeys(keyType);
			}
			*texture = (keyType == -1) ? setTexture("bomberman_assets/wallpapers/keyMappingNumpad.jpg") :
				(keyType == 1) ? setTexture("bomberman_assets/wallpapers/keyMappingwasd.jpg") :
				setTexture("bomberman_assets/wallpapers/keyMappingArrow.jpg") ;
		}
		if (keys.input() == UP && menu != KEYMAPPING){
			sound.playFX(SWIPE);
			if (menu == VOLUME)
				vert += (vert < 0.35f)?0.35f:0.0f;
			else
				vert += (vert < 0.7f)?0.35f:0.0f;
		}
		else if (keys.input() == DOWN && menu != KEYMAPPING){
			sound.playFX(SWIPE);
			if (menu == VOLUME)
				vert -= (vert > -0.35f)?0.35f:0.0f;
			else
				vert -= (vert > -0.7f)?0.35f:0.0f;
		}
		else if (keys.input() == ENTER){
			// sound.playFX(BLAST);
			switch (menu){
				case MAIN:
					if (vert == 0.35f){
						*texture = setTexture("bomberman_assets/wallpapers/save.jpg");
						menu = SAVE;
					}
					else if (vert == 0.0f){
						*texture = setTexture("bomberman_assets/wallpapers/save.jpg");
						menu = LOAD;
					}
					else if (vert == -0.7f){
						*texture = setTexture("bomberman_assets/wallpapers/settings.jpg");
						menu = SETTINGS;
					}
					else if (vert == -0.35f){
						exit(0);
					}
					break;
				case SAVE:
					if(vert == 0.7f)
						saveFile(1);
					else if(vert == 0.35f)
						saveFile(2);
					else if(vert == 0.0f)
						saveFile(3);
					else if(vert == -0.35f)
						saveFile(4);
					else if(vert == -0.7f)
						saveFile(5);
					break;
				case LOAD:
					if(vert == 0.7f)
						loadFile("save/slot1.svf");
					else if(vert == 0.35f)
						loadFile("save/slot2.svf");
					else if(vert == 0.0f)
						loadFile("save/slot3.svf");
					else if(vert == -0.35f)
						loadFile("save/slot4.svf");
					else if(vert == -0.7f)
						loadFile("save/slot5.svf");
					break;
				case SETTINGS:
					if (vert == 0.7f){
						*texture = setTexture("bomberman_assets/wallpapers/sound.jpg");
						menu = VOLUME;
						vert = 0.0f;
					}
					else if (vert == 0.35f){
						*texture = setTexture("bomberman_assets/wallpapers/keyMappingArrow.jpg");
						menu = KEYMAPPING;
					}
					else if (vert == 0.0f){
						*texture = setTexture("bomberman_assets/wallpapers/reso.jpg");
						menu = RESOLUTION;
					}
					else if (vert == -0.35f){
						vert = -10.0f;
						*texture = setTexture("bomberman_assets/wallpapers/cheat.jpg");
						menu = CHEATS;
					}
					else if (vert == -0.7f){
						vert = -10.0f;
						*texture = setTexture("bomberman_assets/wallpapers/credits.jpg");
						menu = CREDITS;
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
			*texture = setTexture("bomberman_assets/wallpapers/settings.jpg");
			menu = SETTINGS;
		}
		else{
			*texture = setTexture("bomberman_assets/wallpapers/menu.jpg");
			menu = MAIN;
		}
	}
}
