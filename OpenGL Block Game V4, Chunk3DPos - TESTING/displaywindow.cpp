#include <iostream>
#include "displaywindow.h"
#include "camera.h"
#include "player.h"
#include "gameWorld.h"

extern double last_cursor_xpos, last_cursor_ypos;
extern GameWorld game_world;

double SENSITIVITY = 0.005;

static void cursor_callback_move(GLFWwindow* window, double xpos, double ypos)
{
	Player player = game_world.player;

	game_world.player.look_horizontal(xpos - last_cursor_xpos);
	game_world.player.look_vertical(ypos - last_cursor_ypos);
	last_cursor_xpos = xpos;
	last_cursor_ypos = ypos;
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
	//glfwWaitEvents(); �r ett annat alternativ, vet inte vad det g�r
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