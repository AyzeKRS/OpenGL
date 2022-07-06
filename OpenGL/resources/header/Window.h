#pragma once

#include "Headers.h"

class Window
{
public:
	bool Init();

	GLFWwindow* GetWindow() const;
	void SetWindow(GLFWwindow* win);

private:
	bool CheckInit() const;

	const unsigned int SRC_WIDTH	= 800;
	const unsigned int SRC_HEIGHT	= 600;
	GLFWwindow* window;
};