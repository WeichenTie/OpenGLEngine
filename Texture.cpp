#include "Texture.h"



Texture2D::Texture2D()
{
	glGenTextures(1, &m_ID);
}


void Texture2D::SetTexParameters(GLenum min, GLenum mag, GLenum wrapS, GLenum wrapT)
{
	glActiveTexture(GL_TEXTURE0);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	Unbind();
}

void Texture2D::LoadImage(std::string path, bool genMipMap)
{
	stbi_set_flip_vertically_on_load(true);
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	glActiveTexture(GL_TEXTURE0);
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	if (genMipMap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(bytes);
	Unbind();
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
