/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/bomberman.hpp"

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Checks if glew was successfuly initialized
		if so the OpenGL Version is printed
		if not an error message is printed
*/
void initCheck(){
	system("clear");
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout
			<< RED <<"Failed to Initialize glew:\n"
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
