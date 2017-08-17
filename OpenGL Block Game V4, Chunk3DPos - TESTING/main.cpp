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

//Include my own headers
#include "displaywindow.h"
#include "texIDLoader.h"
#include "camera.h"
#include "masterRenderer.h"
#include "math.h"
#include "ChunkManager.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

DWORD WINAPI chunk_manager_thread_func(void* ptr);
void ErrorHandler(LPTSTR lpszFunction);
void create_chunk_manager_thread(ChunkManager* ptr_chunk_manager);
void close_chunk_manager_thread();

DWORD   threadID_chunk_manager;
HANDLE  handle_chunk_manager;

Displaywindow* p_displaywindow;

Camera player_camera(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f);
double last_xpos, last_ypos;



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
	ChunkManager chunk_manager(player_camera);
	create_chunk_manager_thread(&chunk_manager);

	//Renderer
	MasterRenderer masterRenderer;

	// texture loader
	TexIDLoader texIDLoader;
	const char* cat = "cat.png";
	GLuint catTexID = texIDLoader.LoadTexID(cat);
	const char* greenpic = "greenpixel.png";
	GLuint greenpixel = texIDLoader.LoadTexID(greenpic);

	//sun
	Light sun(glm::vec3(10000000, 20000000, 5000000));

	while (!displaywindow.ShouldClose()) 
	{
		//KEYBOARD INPUT BEGIN
		if (glfwGetKey(displaywindow.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(displaywindow.window, GL_TRUE);
		}

		if (glfwGetKey(displaywindow.window, GLFW_KEY_W) == GLFW_PRESS)
		{
			player_camera.move_forward(-0.1f);
		}

		if (glfwGetKey(displaywindow.window, GLFW_KEY_S) == GLFW_PRESS)
		{
			player_camera.move_forward(0.1f);
		}

		if (glfwGetKey(displaywindow.window, GLFW_KEY_A) == GLFW_PRESS)
		{
			player_camera.move_sideways(-0.1f);
		}

		if (glfwGetKey(displaywindow.window, GLFW_KEY_D) == GLFW_PRESS)
		{
			player_camera.move_sideways(0.1f);
		}

		if (glfwGetKey(displaywindow.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			player_camera.move_up(0.1f);
		}

		if (glfwGetKey(displaywindow.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			player_camera.move_up(-0.1f);
		}
		//KEYBOARD INPUT END

		displaywindow.PollEvents();

		masterRenderer.render(player_camera, sun, chunk_manager.GetChunkMap());

		displaywindow.SwapBuffers();
	}
	close_chunk_manager_thread();
	return 0;
}

DWORD WINAPI chunk_manager_thread_func(void* ptr)
{
	ChunkManager* ptr_chunk_manager = (ChunkManager*)(ptr);
	while (!(p_displaywindow->ShouldClose()))
	{
		ptr_chunk_manager->loop();
	}
	return 0;
}

void create_chunk_manager_thread(ChunkManager* ptr_chunk_manager)
{
	// Create the thread to begin execution on its own.
	handle_chunk_manager = CreateThread(
		NULL,						// default security attributes
		0,							// use default stack size  
		chunk_manager_thread_func,  // thread function name
		(void*)ptr_chunk_manager,			// argument to thread function 
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