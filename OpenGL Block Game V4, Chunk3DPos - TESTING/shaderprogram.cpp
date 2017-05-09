#include "shaderprogram.h"

void Shaderprogram::Bind()
{
	glUseProgram(programID);
}

void Shaderprogram::Unbind()
{
	glUseProgram(0);
}

GLuint Shaderprogram::CreateShader(const std::string& text, GLenum shadertype)
{
	GLuint shader = glCreateShader(shadertype);

	if (shader == 0) {
		std::cerr << "Error: Shader creation failed" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1] = { text.length() };
	shaderSourceStrings[0] = text.c_str();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

	return shader;
}

std::string Shaderprogram::LoadShader(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "Unable to load shader with file name: " << filename << std::endl;
	}
	return output;
}

void Shaderprogram::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}

}