/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/bomberman.hpp"

# include <cmath>
# include <unistd.h>

int main(){
	Sound sound;
	Keys keys;
	// sound.playloop();
	sound.playOST(PRECIPICE);

  // glfw: initialize and configure
  glfwInit();
  setVersion();

  // glfw window creation
  GLFWwindow* window = glfwCreateWindow(1280, 800, "LearnOpenGL", NULL, NULL);
  if (!window){
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
	keys.setWindow(window);

	//Checking if glew Initialized correctly
  initCheck();

	displayStart(sound, keys, window);

  return 0;
}
