//Include GLEW  
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>

//Include GLM
#include <glm\glm.hpp>

//Include the standard C++ headers  
#include <stdio.h>  
#include <stdlib.h>
#include <cstdint>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

//Include my own headers
#include "displaywindow.h"
#include "gameWorld.h"
#include "ChunkManager.h"
#include "texIDLoader.h"
#include "masterRenderer.h"

#include "player.h"
#include "camera.h"


//forward declarations
DWORD WINAPI chunk_manager_thread_func(void* ptr);
void ErrorHandler(LPTSTR lpszFunction);
void create_chunk_manager_thread();
void close_chunk_manager_thread();
void check_keyboard_input(Displaywindow &displaywindow, Player &player);

//Chunk Manager Thread and Handle
DWORD   threadID_chunk_manager;
HANDLE  handle_chunk_manager;

//for cursor callback
double last_cursor_xpos, last_cursor_ypos;

//Displaywindow pointer
Displaywindow* p_displaywindow;

//World
GameWorld game_world;

int main()
{
	//init glfw
	glfwInit();

	//create GLFWwindow and make context current
	Displaywindow displaywindow = Displaywindow(1600, 900, "title", nullptr, nullptr);
	p_displaywindow = &displaywindow;

	//initialize glew
	glewExperimental = GL_TRUE;
	glewInit();

	//Chunkmanager
	create_chunk_manager_thread();

	//Renderer
	MasterRenderer masterRenderer;

	// texture loader
	TexIDLoader texIDLoader;
	const char* cat = "cat.png";
	GLuint catTexID = texIDLoader.LoadTexID(cat);
	const char* greenpic = "greenpixel.png";
	GLuint greenpixel = texIDLoader.LoadTexID(greenpic);

	//Main game loop
	while (!displaywindow.ShouldClose()) 
	{
		displaywindow.PollEvents();
		check_keyboard_input(displaywindow, game_world.player);

		masterRenderer.render(game_world.player.get_camera(), game_world.sun, game_world.chunk_map);

		std::cout << game_world.player.get_pos().x << ", " << game_world.player.get_pos().y << ", " << game_world.player.get_pos().z << std::endl;

		displaywindow.SwapBuffers();
	}
	close_chunk_manager_thread();
	return 0;
}

void check_keyboard_input(Displaywindow &displaywindow, Player &player)
{
	//KEYBOARD INPUT BEGIN
	if (glfwGetKey(displaywindow.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(displaywindow.window, GL_TRUE);
	}

	if (glfwGetKey(displaywindow.window, GLFW_KEY_W) == GLFW_PRESS)
	{
		player.move_forward(-1);
	}

	if (glfwGetKey(displaywindow.window, GLFW_KEY_S) == GLFW_PRESS)
	{
		player.move_forward(1);
	}

	if (glfwGetKey(displaywindow.window, GLFW_KEY_A) == GLFW_PRESS)
	{
		player.move_sideways(-1);
	}

	if (glfwGetKey(displaywindow.window, GLFW_KEY_D) == GLFW_PRESS)
	{
		player.move_sideways(1);
	}

	if (glfwGetKey(displaywindow.window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		player.move_up(1);
	}

	if (glfwGetKey(displaywindow.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		player.move_up(-1);
	}
	//KEYBOARD INPUT END
}

DWORD WINAPI chunk_manager_thread_func(void* ptr)
{
	ChunkManager chunk_manager;
	while (!(p_displaywindow->ShouldClose()))
	{
		chunk_manager.loop();
	}
	return 0;
}

void create_chunk_manager_thread()
{
	// Create the thread to begin execution on its own.
	handle_chunk_manager = CreateThread(
		NULL,						// default security attributes
		0,							// use default stack size  
		chunk_manager_thread_func,  // thread function name
		nullptr,			        // argument to thread function 
		0,							// use default creation flags 
		&threadID_chunk_manager);   // returns the thread identifier 

	// Check the return value for success.
	// If CreateThread fails, terminate execution. 
	// This will automatically clean up threads and memory. 
	if (threadID_chunk_manager == NULL)
	{
		ErrorHandler(TEXT("CreateThread"));
		ExitProcess(3);
	}

}

void close_chunk_manager_thread()
{
	WaitForMultipleObjects(1, &handle_chunk_manager, TRUE, INFINITE);
	// Close all thread handles and free memory allocations.
	CloseHandle(handle_chunk_manager);

}

void ErrorHandler(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code.

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message.

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	// Free error-handling buffer allocations.

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}