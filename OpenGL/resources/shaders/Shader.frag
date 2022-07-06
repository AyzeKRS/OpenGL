#version 330 core

out vec4 fragColour;
in vec3 ourColour;

void main()
{
	fragColour = vec4(ourColour, 1.0f);
}