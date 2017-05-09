#include "texIDLoader.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

TexIDLoader::TexIDLoader(){}

GLuint TexIDLoader::LoadTexID(const std::string& filename)
{
	GLuint texID;

	//the image's width height, numcomponents = rbga = 4
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL) {
		std::cerr << "Texture loading failed for texture: " << filename << std::endl;
	}

	//only 1 texture per Texture class
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//options

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.0f);

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	//when youre done with the image
	stbi_image_free(imageData);

	return texID;
}

//Texture::~Texture() 
//{
//	//delete texture
//	glDeleteTextures(1, &texID);
//}