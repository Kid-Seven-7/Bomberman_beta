/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/keys.hpp"
# include <iostream>
# include <unistd.h>

Keys::~Keys(){}

Keys::Keys()
:_mode(ARROW), _up(265), _down(264), _left(263), _right(262)
{
	this->_myShader("src/vert.shader", "src/frag.shader");
}

void Keys::setKeys(int mode){
	if (mode == NUMPAD){
		this->_up = 328;
		this->_down = 322;
		this->_left = 324;
		this->_right = 326;
	}else if (mode == WASD){
		this->_up = 87;
		this->_down = 83;
		this->_left = 65;
		this->_right = 68;
	}else{
		this->_up = 265;
		this->_down = 264;
		this->_left = 263;
		this->_right = 262;
	}
}
void 			Keys::setWindow(GLFWwindow *window){
	this->_window = window;
}

void 			Keys::setShader(Shader myShader){
	this->_myShader = myShader;
}

void 			Keys::setSound(Sound &sound){
	this->_sound = sound;
}

void 			Keys::setTexture(unsigned int *texture){
	this->_texture = texture;
}

int Keys::input(GLFWwindow *window){
	int ret = 0;

	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : UP;
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : DOWN;
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : LEFT;
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : RIGHT;
	// else if (glfwGetKey(window, GLFW_KEY_) == GLFW_PRESS)
	// 	ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	// else if (glfwGetKey(window, GLFW_KEY_) == GLFW_PRESS)
	// 	ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	// else if (glfwGetKey(window, GLFW_KEY_) == GLFW_PRESS)
	// 	ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;

	return (ret);
}
