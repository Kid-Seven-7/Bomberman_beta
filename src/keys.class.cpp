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

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Keys destructor
*/
Keys::~Keys(){}

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Keys constructor
*/
Keys::Keys()
:_mode(ARROW)
{}

/*
	Parameters:
		int mode- A MACRO defining the current key mode in use
	Return:
		void
	Synopsis:
		Uses the 'mode' to determine which input system to use
*/
void Keys::setKeys(int mode){
	this->_mode = (mode == NUMPAD) ? NUMPAD : (mode == WASD) ? WASD : ARROW;
}

/*
	Parameters:
		GLFWwindow *window- A pointer to a GLFW window instance
	Return:
		void
	Synopsis:
		Sets the '_window' variable the instance passed in
*/
void 			Keys::setWindow(GLFWwindow *window){
	this->_window = window;
}

int 			Keys::getMode(){
	return(this->_mode);
}

/*
	Parameters:
		void
	Return:
		int ret- A MACRO defining what action should be taken based on key input
	Synopsis:
		Listens for keys presses and uses the current key mode to determine
		which action MACRO to return
*/
int Keys::input(){
	int ret = 0;

	if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		return (EXIT);
	if (glfwGetKey(this->_window, GLFW_KEY_N) == GLFW_PRESS)
		return (NEXT);
	if (glfwGetKey(this->_window, GLFW_KEY_B) == GLFW_PRESS)
		return (PREV);
	if (glfwGetKey(this->_window, GLFW_KEY_ENTER) == GLFW_PRESS)
		return (ENTER);
	if (glfwGetKey(this->_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		return (SPACE);

	if (this->_mode == WASD){
		if (glfwGetKey(this->_window, GLFW_KEY_W) == GLFW_PRESS)
			ret = UP;
		if (glfwGetKey(this->_window, GLFW_KEY_S) == GLFW_PRESS)
			ret = DOWN;
		if (glfwGetKey(this->_window, GLFW_KEY_A) == GLFW_PRESS)
			ret = LEFT;
		if (glfwGetKey(this->_window, GLFW_KEY_D) == GLFW_PRESS)
			ret = RIGHT;
	}else if (this->_mode == NUMPAD){
		if (glfwGetKey(this->_window, GLFW_KEY_KP_8) == GLFW_PRESS)
			ret = UP;
		if (glfwGetKey(this->_window, GLFW_KEY_KP_2) == GLFW_PRESS)
			ret = DOWN;
		if (glfwGetKey(this->_window, GLFW_KEY_KP_4) == GLFW_PRESS)
			ret = LEFT;
		if (glfwGetKey(this->_window, GLFW_KEY_KP_6) == GLFW_PRESS)
			ret = RIGHT;
	}else if (this->_mode == ARROW){
		if (glfwGetKey(this->_window, GLFW_KEY_UP) == GLFW_PRESS)
			ret = UP;
		if (glfwGetKey(this->_window, GLFW_KEY_DOWN) == GLFW_PRESS)
			ret = DOWN;
		if (glfwGetKey(this->_window, GLFW_KEY_LEFT) == GLFW_PRESS)
			ret = LEFT;
		if (glfwGetKey(this->_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			ret = RIGHT;
	}

	return (ret);
}
