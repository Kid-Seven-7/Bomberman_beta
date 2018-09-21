/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# ifndef 			_BOMB_HPP_
# define 			_BOMB_HPP_

# include 		<GL/glew.h>
# include 		<GLFW/glfw3.h>
# include 		<iostream>
# include 		<exception>
# include 		<vector>
# include 		<map>

# include 		"shader.hpp"
# include 		"sound.hpp"

//Color out puts
# define 			RED "\033[0;31m"
# define 			GREEN "\033[0;32m"
# define 			ORANGE "\033[0;33m"
# define 			BLUE "\033[0;34m"
# define 			CYAN "\033[0;36m"
# define 			NC "\033[0m"

//Sounds
# define 			BLAST 10
# define 			SWIPE 11
# define 			FOOTSTEP 12
# define 			DEATH 13
# define 			ONEUP 14
# define 			GHOST 15

//menus
# define 			MAIN 20
# define 			START 21
# define 			SAVE 22
# define 			LOAD 23
# define 			SETTINGS 24
# define 			RESOLUTION 25
# define 			VOLUME 26
# define 			KEYMAPPING 27
# define 			CHEATS 28
# define 			CREDITS 29

//Key returns
# define UP 100
# define DOWN 101
# define LEFT 102
# define RIGHT 103
# define ACTION 104
// # define
// # define

//Voids
void 					setVersion();
void 					initCheck();
void 					processInput(GLFWwindow *window, Shader myShader, Sound &sound, unsigned int *texture);

//char *s
const char 		*vert();
const char 		*frag();
const char 		*ivert();
const char 		*ifrag();

//ints
unsigned int 	setTexture(std::string file);

bool 					does_file_exist(std::string fileName);

#endif
