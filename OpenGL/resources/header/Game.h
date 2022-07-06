#pragma once

#include "Headers.h"
#include "Window.h"
#include "Shader.h"

void FrameBufferSizeCallback
(
	GLFWwindow* window,
	int width, int height
);

class Game
{
public:
	//Game();

	int Run();
	bool Init();

private:
	void Update();
	void Render();

	// CREATE OBJECTS
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void GenObjects();

	void GenVAO();
	void GenVBO();
	void GenEBO();
	
	void DrawTriangles() const;
	// END OF OBJECTS

	bool CheckGLAD() const;

	void ProcessKeyboardInput(GLFWwindow* window) const;

	Window* window;
	Shader* testShader;
};