#pragma once
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

enum
{
	VERTEX,
	FRAGMENT,

	NUM_SHADERS
};

class Shader
{
public:
	Shader(const std::string& name);
	void Start();
	void Stop();
	virtual ~Shader();
protected:
	GLuint GetUniformLocation(const char* name) { return glGetUniformLocation(id, name); };
	void LoadMatrix(GLuint location, glm::mat4 matrix) { glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]); };
	void LoadInt(GLuint location, int value) { glUniform1i(location, value); };
private:
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	GLuint id;
	GLuint shaders[NUM_SHADERS];
};