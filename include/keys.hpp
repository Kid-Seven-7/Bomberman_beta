/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# ifndef 				__KEYS_HPP__
# define 				__KEYS_HPP__

# include 			<GLFW/glfw3.h>

# include 			"shader.hpp"
# include 			"sound.hpp"

//Color out puts
# define 				RED "\033[0;31m"
# define 				GREEN "\033[0;32m"
# define 				ORANGE "\033[0;33m"
# define 				BLUE "\033[0;34m"
# define 				CYAN "\033[0;36m"
# define 				NC "\033[0m"

//Key returns
# define 				UP 100
# define 				DOWN 101
# define 				LEFT 102
# define 				RIGHT 103
# define 				ACTION 104
# define 				ENTER 105
# define 				NEXT 106
# define 				PREV 107
# define 				EXIT 108

//KEYMODE
# define 				ARROW 200
# define 				WASD 201
# define 				NUMPAD 202

class Keys{
	private:
		int 				_mode;
		GLFWwindow* _window;

	public:
		Keys();
		~Keys();

		void 				setKeys(int mode);
		void 				setWindow(GLFWwindow *window);
		int					getMode();
		int 				input();
};

# endif
