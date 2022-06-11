#include "ShaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");
	
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int id, const char* type)
{
	GLint success;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
			std::cout<< "SHADER_COMPILATION_ERROR for: " << std::string(type) << std::endl << std::string(infoLog) << std::endl;
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetProgramInfoLog(id, 1024, NULL, infoLog);
			std::cout << "PROGRAM_LINKING_ERROR: " + std::string(infoLog) + "\n";
		}
	}
}
