#include "../resources/header/Shader.h"

/// <summary>
/// Shader constructor, checking the files are valid
/// and create the shader program
/// </summary>
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. Retrieve vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// Ensure ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		vertexCode		= vShaderStream.str();
		fragmentCode	= fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout
			<< "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ"
			<< std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. Compile shaders
	unsigned int vertex	
		= glCreateShader(GL_VERTEX_SHADER);

	unsigned int fragment
		= glCreateShader(GL_FRAGMENT_SHADER);

	int success = 0;

	// Vertex shader
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	CheckErrors(success, vertex, "VERTEX::COMPILATION_FAILED");

	// Fragment shader
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	CheckErrors(success, fragment, "FRAGMENT::COMPILATION_FAILED");

	// Shader program
	ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	CheckErrors(success, ID, "PROGRAM::LINKING_FAILED");

	// 3. Delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

/// <summary>
/// Check shader compile errors
/// </summary>
void Shader::CheckErrors
(
	const int& success,
	const unsigned int& shader,
	const std::string errorText
) const
{
	char infoLog[512];

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout
			<< "ERROR::SHADER::"
			<< errorText
			<< "\n"
			<< infoLog
			<< std::endl;
	}
}

/// <summary>
/// Use the shader program
/// </summary>
void Shader::Use() const
{
	glUseProgram(ID);
}

/// <summary>
/// Utility unform setter bool function
/// </summary>
void Shader::SetBool(const std::string& name, const bool& value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

/// <summary>
/// Utility unform setter int function
/// </summary>
void Shader::SetInt(const std::string& name, const int& value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

/// <summary>
/// Utility unform setter float function
/// </summary>
void Shader::SetFloat(const std::string& name, const float& value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}