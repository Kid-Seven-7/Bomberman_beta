/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# ifndef 			KEYS_HPP
# define 			KEYS_HPP

# include 		"shader.hpp"
# include 		"sound.hpp"

//Color out puts
# define 			RED "\033[0;31m"
# define 			GREEN "\033[0;32m"
# define 			ORANGE "\033[0;33m"
# define 			BLUE "\033[0;34m"
# define 			CYAN "\033[0;36m"
# define 			NC "\033[0m"

//Key returns
# define UP 100
# define DOWN 101
# define LEFT 102
# define RIGHT 103
# define ACTION 104

//KEYMODE
# define ARROW 200
# define WASD 201
# define NUMPAD 202

// # define 			LOOP1 16
// # define 			LOOP2 17
// # define 			LOOP3 18
// # define 			LOOP4 19
// # define 			LOOP5 20
// # define 			LOOP6 21
// # define 			LOOP7 22
// # define 			LOOP8 23
// # define 			LOOP9 24

// # include "bomberman.hpp"
# include 		<GLFW/glfw3.h>

class Keys{
	private:
		int _mode;
		int _up;
		int _down;
		int _left;
		int _right;
		GLFWwindow* _window;
		Shader _myShader;
		Sound& _sound;
		unsigned int* _texture;

	public:
		Keys();
		~Keys();

		void 			setKeys(int mode);
		void 			setWindow(GLFWwindow *window);
		void 			setShader(Shader myShader);
		void 			setSound(Sound &sound);
		void 			setTexture(unsigned int *texture);
		int 			input(GLFWwindow *window);
};

#endif
