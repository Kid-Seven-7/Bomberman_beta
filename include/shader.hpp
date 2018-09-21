/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# ifndef 					__SHADER_HPP__
# define 					__SHADER_HPP__

# include 				<GLFW/glfw3.h>
# include 				<glm/glm.hpp>
# include 				<string>
# include 				<fstream>
# include 				<sstream>
# include 				<iostream>

//Color out puts
# define 					RED "\033[0;31m"
# define 					GREEN "\033[0;32m"
# define 					ORANGE "\033[0;33m"
# define 					BLUE "\033[0;34m"
# define 					CYAN "\033[0;36m"
# define 					NC "\033[0m"

class Shader{
	public:
		unsigned int 	ID;
		Shader(const char* vertexPath, const char* fragmentPath);
		void 					use();

	private:
		void 					checkCompileErrors(GLuint shader, std::string type);
};
#endif
