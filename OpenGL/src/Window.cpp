#include "../resources/header/Window.h"

/// <summary>
/// Create the window
/// </summary>
bool Window::Init()
{
	window
		= glfwCreateWindow
		(
			SRC_WIDTH, SRC_HEIGHT,
			"OpenGLTut", NULL, NULL
		);

	return CheckInit();
}

/// <summary>
/// Check if the window fails to instantiate
/// </summary>
bool Window::CheckInit() const
{
	if (window == NULL)
	{
		std::cout
			<< "Failed to create GLFW window"
			<< std::endl;

		glfwTerminate();
		return false;
	}

	return true;
}

/// <summary>
/// Gets the window pointer
/// </summary>
GLFWwindow* Window::GetWindow() const
{
	return window;
}

/// <summary>
/// Sets the window pointer
/// </summary>
void Window::SetWindow(GLFWwindow* win)
{
	window = win;
}