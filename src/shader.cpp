/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/shader.hpp"

/*
	Parameters:
		const char* vertexPath- Path to vertex shader source code
		const char* fragmentPath- Path to fragment shader source code
	Return:
		void
	Synopsis:
		Shader simple constructor
*/
Shader::Shader(const char* vertexPath, const char* fragmentPath){
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	try{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}catch (std::ifstream::failure e){
		std::cout
			<< RED
			<< "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"
			<< NC
			<< std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Sets shader as active
*/
void Shader::use(){
	glUseProgram(ID);
}

/*
	Parameters:
		GLuint shader- Shader ID
		std::string type- Shader type
	Return:
		void
	Synopsis:
		Checks for compilation errors
*/
void Shader::checkCompileErrors(GLuint shader, std::string type){
	GLint success;
	GLchar infoLog[1024];
	if(type != "PROGRAM"){
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success){
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout
				<< RED
				<< "ERROR::SHADER_COMPILATION_ERROR of type: "
				<< NC
				<< type
				<< "\n"
				<< infoLog
				<< RED<< "\n -- --------------------------------------------------- -- "
				<< NC
				<< std::endl;
		}
	}else{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if(!success){
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout
				<< RED
				<< "ERROR::PROGRAM_LINKING_ERROR of type: "
				<< NC
				<< type
				<< "\n"
				<< infoLog
				<< RED
				<< "\n -- --------------------------------------------------- -- "
				<< NC
				<< std::endl;
		}
	}
}
