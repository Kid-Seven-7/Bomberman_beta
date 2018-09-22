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
:_mode(ARROW), _up(265), _down(264), _left(263), _right(262)
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
	this->_up = (mode == NUMPAD) ? 328 : (mode == WASD) ? 87 : 265;
	this->_down = (mode == NUMPAD) ? 322 : (mode == WASD) ? 83 : 264;
	this->_left = (mode == NUMPAD) ? 324 : (mode == WASD) ? 65 : 263;
	this->_right = (mode == NUMPAD) ? 326 : (mode == WASD) ? 68 : 262;
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

	//Numpad keys
	if (glfwGetKey(this->_window, GLFW_KEY_8) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? UP : 265;
	else if (glfwGetKey(this->_window, GLFW_KEY_6) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? DOWN : 265;
	else if (glfwGetKey(this->_window, GLFW_KEY_4) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? LEFT : 265;
	else if (glfwGetKey(this->_window, GLFW_KEY_2) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? RIGHT : 265;

	//WASD keys
	else if (glfwGetKey(this->_window, GLFW_KEY_W) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? UP : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(this->_window, GLFW_KEY_A) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? DOWN : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(this->_window, GLFW_KEY_S) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? LEFT : (this->_mode == NUMPAD) ? 87 : 265;
	else if (glfwGetKey(this->_window, GLFW_KEY_D) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? RIGHT : (this->_mode == NUMPAD) ? 87 : 265;

	//Arrow keys
	else if (glfwGetKey(this->_window, GLFW_KEY_UP) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : UP;
	else if (glfwGetKey(this->_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : DOWN;
	else if (glfwGetKey(this->_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : LEFT;
	else if (glfwGetKey(this->_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : RIGHT;

	//Misc keys
	else if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		ret = EXIT;
	else if (glfwGetKey(this->_window, GLFW_KEY_N) == GLFW_PRESS)
		ret = NEXT;
	else if (glfwGetKey(this->_window, GLFW_KEY_B) == GLFW_PRESS)
		ret = PREV;
	else if (glfwGetKey(this->_window, GLFW_KEY_ENTER) == GLFW_PRESS)
		ret = ENTER;
	// else if (glfwGetKey(this->_window, GLFW_KEY_) == GLFW_PRESS)
	// 	ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;
	// else if (glfwGetKey(this->_window, GLFW_KEY_) == GLFW_PRESS)
	// 	ret = (this->_mode == WASD) ? 328 : (this->_mode == NUMPAD) ? 87 : 265;

	return (ret);
}
