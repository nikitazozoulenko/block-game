#ifndef SHADERPOGRAM_H
#define SHADERPOGRAM_H
//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>

class Shaderprogram 
{
public:
	static std::string LoadShader(const std::string& filename);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static GLuint CreateShader(const std::string& text, GLenum shadertype);

	virtual void Bind();
	virtual void Unbind();
protected:
	//programID
	GLuint programID;
private:
};

#endif // !SHADERPOGRAM_H
