#pragma once
#include "Headers.h"

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	// Use shader
	void Use() const;

	// Utility uniform functions
	void SetBool(const std::string& name, const bool& value) const;
	void SetInt(const std::string& name, const int& value) const;
	void SetFloat(const std::string& name, const float& value) const;
	
	// Program ID
	unsigned int ID;

private:
	void CheckErrors
	(
		const int& success,
		const unsigned int& shader,
		const std::string errorText
	) const;
};