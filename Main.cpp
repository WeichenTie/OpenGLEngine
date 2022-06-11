#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include "Texture.h"

#define WIDTH 800
#define HEIGHT 800

int main() {
	// Start up GLFW
	glfwInit();

	// Tell GLFW what version of OpneGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] =
	{ 
		-0.5f, -0.5f, 0.0f,     1.0f, 0.3f, 0.02f,   0.0f, 0.0f,// Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 0.3f, 1.0f,    0.0f, 1.0f,// Lower right corner
		 0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.32f,   1.0f, 1.0f, // Upper corner
		 0.5f, -0.5f , 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,// Inner left
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0,2,1,0,3,2
	};
	// Create the window and set it to the current context;
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGlTest", NULL, NULL);
	// If window cannot be created
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Load in GLAD
	gladLoadGL();
	glViewport(0, 0, WIDTH, HEIGHT);

	Shader shaderProgram("default.vert", "default.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAOAttribLayouts layout = VAOAttribLayouts();
	layout.AddAttrib(3, GL_FLOAT, GL_FALSE);
	layout.AddAttrib(3, GL_FLOAT, GL_FALSE);
	layout.AddAttrib(2, GL_FLOAT, GL_FALSE);
	VAO1.AddAttribs(VBO1, layout);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "uScale");

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	Texture2D tex2D = Texture2D();
	tex2D.SetTexParameters(GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	tex2D.LoadImage("pop_cat.png", true);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	OrthographicCamera camera = OrthographicCamera((float)WIDTH, (float)HEIGHT);


	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 1.5f);
		tex2D.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwPollEvents();

		glfwSwapBuffers(window);
	}
	// Clean up

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	//glDeleteTextures(1, &texture);
	shaderProgram.Delete();


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}