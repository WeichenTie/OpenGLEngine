#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <memory>
#include <glad/glad.h>
#include "VBO.h"
#include <vector>

struct VAOAttrib
{
	int count;
	int type;
	bool normalise;
	int offset;
};


class VAOAttribLayouts
{
public:
	VAOAttribLayouts();
	void AddAttrib(int count, int type, bool normalise);
	static int GetTypeSize(int type);
	int GetStride() { return m_Stride; };
	std::vector<VAOAttrib> GetAttribs() { return m_Attribs; };

private:
	std::vector<VAOAttrib> m_Attribs;
	int m_Stride;
};


class VAO
{

public:
	GLuint ID;
	VAO();

	void AddAttribs(VBO VBO, VAOAttribLayouts layout);
	void Bind();
	void Unbind();
	void Delete();

};



#endif