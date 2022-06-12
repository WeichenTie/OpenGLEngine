#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <unordered_map>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragmentFile);
		
	void Activate();
	void Delete();
	GLint GetUniformLocation(std::string uniformName);
private:
	GLuint m_ID;
	std::unordered_map<std::string, GLint> m_UniformMap;
	void compileErrors(unsigned int shader, const char* type);
};


#endif