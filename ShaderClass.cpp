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
	
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);
	compileErrors(m_ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(m_ID);
}

void Shader::Delete()
{
	glDeleteProgram(m_ID);
}

GLint Shader::GetUniformLocation(std::string uniformName)
{
	if (m_UniformMap.find(uniformName) != m_UniformMap.end())
	{
		return m_UniformMap[uniformName];
	}
	GLint location = glGetUniformLocation(m_ID, uniformName.c_str());
	if (location == -1)
	{
		std::cout << "WARNING: UNIFORM \"" << uniformName << "\" DOES NOT EXIST" << std::endl;
	}
	m_UniformMap[uniformName] = location;
	return location;
}

void Shader::compileErrors(unsigned int m_ID, const char* type)
{
	GLint success;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(m_ID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			glGetShaderInfoLog(m_ID, 1024, NULL, infoLog);
			std::cout<< "SHADER_COMPILATION_ERROR for: " << std::string(type) << std::endl << std::string(infoLog) << std::endl;
		}
	}
	else
	{
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);
			std::cout << "PROGRAM_LINKING_ERROR: " + std::string(infoLog) + "\n";
		}
	}
}
