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

#include "displaywindow.h"
#include "model.h"
#include "texIDLoader.h"
#include "camera.h"
#include "masterRenderer.h"
#include "modelLoader.h"
#include "math.h"
#include "ChunkManager.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

DWORD WINAPI chunk_manager_thread_func(void* ptr);
void ErrorHandler(LPTSTR lpszFunction);
void create_chunk_manager_thread();
void close_chunk_manager_thread();

constexpr int MAX_THREADS = 1;

DWORD   dwThreadIdArray[MAX_THREADS];
HANDLE  hThreadArray[MAX_THREADS];

Displaywindow* p_displaywindow;

//static std::vector<GLuint> vector_block_texIDs;

Camera player_camera(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f);
double last_xpos, last_ypos;

ChunkManager chunkManager(player_camera);

int main()
{
	//init glfw
	glfwInit();

	//create GLFWwindow and make context current
	Displaywindow displaywindow = Displaywindow(800, 600, "title", nullptr, nullptr);
	p_displaywindow = &displaywindow;

	//initialize glew
	glewExperimental = GL_TRUE;
	glewInit();


	//Camera and chunkmanager
	Chunk3DPos::UpdateCamera(player_camera);

	create_chunk_manager_thread();


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

		masterRenderer.render(player_camera, sun, chunkManager.GetChunkMap());

		displaywindow.SwapBuffers();
	}
	close_chunk_manager_thread();
	return 0;
}

DWORD WINAPI chunk_manager_thread_func(void* ptr)
{
	while (!(p_displaywindow->ShouldClose()))
	{
		chunkManager.loop();
	}
	return 0;
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

void create_chunk_manager_thread()
{
	// Create MAX_THREADS worker threads.

	for (int i = 0; i<MAX_THREADS; i++)
	{

		// Create the thread to begin execution on its own.

		hThreadArray[i] = CreateThread(
			NULL,                   // default security attributes
			0,                      // use default stack size  
			chunk_manager_thread_func,       // thread function name
			nullptr,          // argument to thread function 
			0,                      // use default creation flags 
			&dwThreadIdArray[i]);   // returns the thread identifier 


									// Check the return value for success.
									// If CreateThread fails, terminate execution. 
									// This will automatically clean up threads and memory. 

		if (hThreadArray[i] == NULL)
		{
			ErrorHandler(TEXT("CreateThread"));
			ExitProcess(3);
		}
	} // End of main thread creation loop.

}

void close_chunk_manager_thread()
{
	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

	// Close all thread handles and free memory allocations.

	for (int i = 0; i<MAX_THREADS; i++)
	{
		CloseHandle(hThreadArray[i]);
	}
}