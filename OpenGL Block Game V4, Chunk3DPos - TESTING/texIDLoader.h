#ifndef TEXIDLOADER_H
#define TEXIDLOADER_H

#include <GL\glew.h>
#include <string>

class TexIDLoader 
{
public:
	TexIDLoader();
	static GLuint LoadTexID(const std::string& const filename);
private:
};

#endif //TEXIDLOADER_H
