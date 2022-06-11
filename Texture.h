#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include <string>
class Texture2D
{
public:
	Texture2D();
	
	void SetTexParameters(GLenum min, GLenum mag, GLenum wrapS, GLenum wrapT);

	void LoadImage(std::string path, bool genMipMap);

	void Bind();
	void Unbind();
private:
	GLuint m_ID;

};




#endif;