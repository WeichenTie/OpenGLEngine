#include "VAO.h";

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}


void VAO::AddAttribs(VBO VBO, VAOAttribLayouts layout)
{
	Bind();
	VBO.Bind();
	std::vector<VAOAttrib> attribs = layout.GetAttribs();
	for (int i = 0; i < attribs.size(); i++) {
		VAOAttrib attrib = attribs[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalise, layout.GetStride(), (void*)attrib.offset);
	}
	Unbind();
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}
void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}


VAOAttribLayouts::VAOAttribLayouts()
{
	m_Attribs = std::vector<VAOAttrib>();
}

void VAOAttribLayouts::AddAttrib(int count, int type, bool normalise)
{
	struct VAOAttrib newAttrib = { count, type, normalise, m_Stride };
	m_Attribs.push_back(newAttrib);
	m_Stride += count * GetTypeSize(type);
}

int VAOAttribLayouts::GetTypeSize(int type)
{
	return 4;
}
