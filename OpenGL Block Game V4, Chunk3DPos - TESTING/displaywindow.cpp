#include <iostream>
#include "displaywindow.h"
#include "camera.h"
#include "player.h"
#include "gameWorld.h"

extern double last_cursor_xpos, last_cursor_ypos;
extern GameWorld game_world;

static void cursor_callback_move(GLFWwindow* window, double xpos, double ypos)
{
	game_world.player.get_camera().look_horizontal((xpos - last_cursor_xpos)*0.01);
	game_world.player.get_camera().look_vertical((ypos - last_cursor_ypos)*0.01);
	last_cursor_xpos = xpos;
	last_cursor_ypos = ypos;

	//TODO: MAKE PLAYER ALSO LOOK AROUND, NOT JUST THE CAMERA
}

Displaywindow::Displaywindow(const int width, const int height, const char* const title, GLFWmonitor* glfw_monitor, GLFWwindow* glfw_other_window)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(width, height, title, glfw_monitor, glfw_other_window);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//key callbacks
	glfwSetCursorPosCallback(window, cursor_callback_move);
}

void Displaywindow::PollEvents()
{
	glfwPollEvents();
}

void Displaywindow::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void Displaywindow::ClearColor(const float r, const float b, const float g, const float a)
{

}

int Displaywindow::ShouldClose()
{
	return glfwWindowShouldClose(window);
}