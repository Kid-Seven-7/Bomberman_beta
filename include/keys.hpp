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

//Color out puts
# define 			RED "\033[0;31m"
# define 			GREEN "\033[0;32m"
# define 			ORANGE "\033[0;33m"
# define 			BLUE "\033[0;34m"
# define 			CYAN "\033[0;36m"
# define 			NC "\033[0m"

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

class Key{
	private:
		int _up;
		int _down;
		int _left;
		int _right;

	public:
		Keys();
		~Keys();

		void 			setKeys(std::string type);
		int 			input();
};

#endif
