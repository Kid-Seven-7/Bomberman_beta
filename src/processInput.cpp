# include "../include/bomberman.hpp"

int up = 265;
int down = 264;
int left = 263;
int right = 262;

void mapKeys(int keyType){
	up = (keyType == -1) ? 328 : (keyType == 1) ? 87 : 265;
	down = (keyType == -1) ? 322 : (keyType == 1) ? 83 : 264;
	left = (keyType == -1) ? 324 : (keyType == 1) ? 65 : 263;
	right = (keyType == -1) ? 326 : (keyType == 1) ? 68 : 262;
}

void loadFile(std::string filepath){
	if (does_file_exist(filepath))
		std::cout << "file exists" << '\n';
	else
		std::cout << "no such file" << '\n';
}

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

void processInput(GLFWwindow *window, Shader myShader, Sound &sound, unsigned int *texture)
{
	static unsigned char i = 0;
	static unsigned int menu = MAIN;
	static int keyType = 0;
	static float vert, hori = 0.0f;
	int vertexPosLocation = glGetUniformLocation(myShader.ID, "newPosition");

	glUniform4f(vertexPosLocation, hori, vert, 0.2f, 1.0f);

	if (++i % 4 == 0){
		if (menu == KEYMAPPING){
			vert = -10.0f;
			if (glfwGetKey(window, right) == GLFW_PRESS){
				sound.playFX(SWIPE);
				keyType += (keyType < 1)?1:0;
			}
			else if (glfwGetKey(window, left) == GLFW_PRESS){
				sound.playFX(SWIPE);
				keyType -= (keyType > -1)?1:0;
			}
			else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
				mapKeys(keyType);
			}
			*texture = (keyType == -1) ? setTexture("bomberman_assets/wallpapers/keyMappingNumpad.jpg") :
				(keyType == 1) ? setTexture("bomberman_assets/wallpapers/keyMappingwasd.jpg") :
				setTexture("bomberman_assets/wallpapers/keyMappingArrow.jpg") ;
		}
		if ((glfwGetKey(window, up) == GLFW_PRESS) && menu != KEYMAPPING){
			sound.playFX(SWIPE);
			if (menu == VOLUME)
				vert += (vert < 0.35f)?0.35f:0.0f;
			else
				vert += (vert < 0.7f)?0.35f:0.0f;
		}
		else if ((glfwGetKey(window, down) == GLFW_PRESS) && menu != KEYMAPPING){
			sound.playFX(SWIPE);
			if (menu == VOLUME)
				vert -= (vert > -0.35f)?0.35f:0.0f;
			else
				vert -= (vert > -0.7f)?0.35f:0.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
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
						// std::cout << "Cheat codes" << '\n';
						vert = -10.0f;
						*texture = setTexture("bomberman_assets/wallpapers/cheat.jpg");
						menu = CHEATS;
					}
					else if (vert == -0.7f){
						// std::cout << "credits" << '\n';
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
		else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			sound.playFX(GHOST);
		else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
			sound.nextLoop();
		else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
			sound.prevLoop();
		else if (glfwGetKey(window, right) == GLFW_PRESS && menu == VOLUME){
			if(vert == 0.35f){
				sound.setVolumeLevel("SFX", 10.0f);
				sound.setVolumeLevel("LOOP", 10.0f);
			}else if(vert == 0.0f)
				sound.setVolumeLevel("LOOP", 10.0f);
			else if(vert == -0.35f)
				sound.setVolumeLevel("SFX", 10.0f);
		}
		else if (glfwGetKey(window, left) == GLFW_PRESS && menu == VOLUME){
			if(vert == 0.35f){
				sound.setVolumeLevel("SFX", -10.0f);
				sound.setVolumeLevel("LOOP", -10.0f);
			}else if(vert == 0.0f)
				sound.setVolumeLevel("LOOP", -10.0f);
			else if(vert == -0.35f)
				sound.setVolumeLevel("SFX", -10.0f);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
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
