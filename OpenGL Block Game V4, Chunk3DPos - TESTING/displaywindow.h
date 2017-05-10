#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

//Include GLEW  
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>

class Displaywindow {
public:
	Displaywindow(const int, const int, const char*, GLFWmonitor*, GLFWwindow*);
	void PollEvents();
	void ClearColor(const float, const float, const float, const float);
	void SwapBuffers();
	int ShouldClose();
	GLFWwindow* window;
private:
};

#endif //DISPLAYWINDOW_H
