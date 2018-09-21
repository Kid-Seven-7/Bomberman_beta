/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/bomberman.hpp"

void initCheck(){
	system("clear");
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	if (glewInit() != GLEW_OK)
		std::cout
			<< RED <<"Failed to Initialize glew:\n"
			<< ORANGE << glewGetErrorString(glewInit())
			<< NC << std::endl;
	else
		std::cout
			<< GREEN << "OpenGL version : "
			<< NC << glGetString(GL_VERSION)
			<< '\n' << GREEN
			<< "GLFW version : " << NC
			<< major << "."
			<< minor << "."
			<< revision << std::endl;
}
