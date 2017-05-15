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




//static std::vector<GLuint> vector_block_texIDs;


Camera player_camera(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f);
double last_xpos, last_ypos;

int main()
{
	uint16_t testint1 = 0xffff;
	std::cout << testint1 << std::endl;
	uint16_t testint2 = 0xffff;
	testint2 = testint2 << 1;
	std::cout << testint2 << std::endl;
	//init glfw
	glfwInit();

	//create GLFWwindow and make context current
	Displaywindow displaywindow = Displaywindow(800, 600, "title", nullptr, nullptr);

	//initialize glew
	glewExperimental = GL_TRUE;
	glewInit();

	//Camera and chunkmanager
	Chunk3DPos::UpdateCamera(player_camera);
	ChunkManager chunkManager(player_camera);


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

	for (int x = 0; x != 3; ++x)
	{
		for (int y = 0; y != 3; ++y)
		{
			for (int z = 0; z != 3; ++z)
			{
				chunkManager.create_chunk(x, y, z);
			}
		}
	}

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
	return 0;
}