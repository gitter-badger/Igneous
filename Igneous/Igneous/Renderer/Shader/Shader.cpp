#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader(const std::string& name)
{
	id = glCreateProgram();
	shaders[VERTEX] = CreateShader(LoadShader("resources/shaders/" + name + ".vs"), GL_VERTEX_SHADER);
	shaders[FRAGMENT] = CreateShader(LoadShader("resources/shaders/" + name + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(id, shaders[i]);
	}

	glLinkProgram(id);
	CheckShaderError(id, GL_LINK_STATUS, true, "Error: Shader program failed to link: ");

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(id, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glValidateProgram(id);
	CheckShaderError(id, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid: ");
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::Start()
{
	glUseProgram(id);
}

void Shader::Stop()
{
	glUseProgram(0);
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader creating failed!" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLength[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLength[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLength);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader failed to compile: ");

	return shader;
}