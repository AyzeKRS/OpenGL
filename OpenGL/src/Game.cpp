#include "../resources/header/Game.h"

/// <summary>
/// Inits the program
/// Creates the window, checks both the window and GLAD
/// </summary>
bool Game::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// If running on an Apple device
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
#endif

	// Create new window
	window
		= new Window();

	if (!window->Init())
		return false;
		
	glfwMakeContextCurrent(window->GetWindow());
	glfwSetFramebufferSizeCallback(window->GetWindow(), FrameBufferSizeCallback);

	if (!CheckGLAD())
		return false;

	return true;
}

/// <summary>
/// Runs the update and render loops
/// </summary>
int Game::Run()
{
	// Create shaders
	// REMEMBER SEARCHING STARTS FROM BASE, NOT GAME.CPP
	testShader = new Shader
	(
		"resources/shaders/Shader.vert",
		"resources/shaders/Shader.frag"
	);

	// Create objects
	GenObjects();
	
	// Gameloop; keep running until user says otherwise
	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		Update();
		Render();
	}

	// Delete resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Safely close
	glfwTerminate();

	// Delete objects
	delete window;
	delete testShader;

	return 0;
}

/// <summary>
/// Update loop; process and update data
/// </summary>
void Game::Update()
{
	// Wait for input
	ProcessKeyboardInput(window->GetWindow());
}

/// <summary>
/// Render loop; show anything to be displayed on screen
/// </summary>
void Game::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawTriangles();

	// Swap buffers, poll IO events
	glfwSwapBuffers(window->GetWindow());
	glfwPollEvents();
}

/// <summary>
/// Check if GLAD fails to initialise
/// </summary>
bool Game::CheckGLAD() const
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout
			<< "Failed to initialise GLAD"
			<< std::endl;

		return false;
	}

	return true;
}

/// <summary>
/// Generate Vertex Array Objects
/// </summary>
void Game::GenVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

/// <summary>
/// Generate Vertex Buffer Objects
/// </summary>
void Game::GenVBO()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

/// <summary>
/// Generate Element Buffer Objects
/// </summary>
void Game::GenEBO()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

/// <summary>
/// Generate objects to be rendered
/// </summary>
void Game::GenObjects()
{
	const float vertices[] =
	{
		// Pos					// Colour
		0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	// Bottom right
		-0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	// Bottom left
		0.0f,	0.5f,	0.0f,	0.0f, 0.0f, 1.0f	// Top
	};

	// Bind the VAO first, then bind and set vertex buffers
	// and then configure vertex attributes
	GenVAO();
	GenVBO();
	//GenEBO();

	glBufferData
	(
		GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW
	);

	// Position attribute
	glVertexAttribPointer
	(
		0, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), (void*)0
	);
	glEnableVertexAttribArray(0);

	// Colour attribute
	glVertexAttribPointer
	(
		1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), (void*)(3 * sizeof(float))
	);
	glEnableVertexAttribArray(1);

	// This is allowed, call to glVertexAttribPointer
	// registered VBO as the vertex attribute's bound
	// vertex buffer object so afterwards we can
	// safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO afterwards so other VAO calls will not
	// accidentally modify this VAO, but it rarely happens
	// Modding other VAOs require a call to glBindVertexArray
	// anyways so we generally don't unbind BAOs (nor VBOs)
	// when it is not directly necessary
	glBindVertexArray(0);
}

/// <summary>
/// Get vertex data, draw triangles
/// </summary>
void Game::DrawTriangles() const
{
	testShader->Use();

	// One VAO, no need to bind every time
	// but we will do it to be organised
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

/// <summary>
/// Process all input
/// </summary>
void Game::ProcessKeyboardInput(GLFWwindow* window) const
{
	// Escape pressed, close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Alpha one pressed, wireframe
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Alpha two pressed, fill
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/// <summary>
/// Resize window
/// </summary>
void FrameBufferSizeCallback
(
	GLFWwindow* window,
	int width, int height
)
{
	glViewport(0, 0, width, height);
}