#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H	
#include <glew-2.0.0/include/GL/glew.h>

class Texture2D
{
public:
	GLuint ID;
	//image dimensions
	GLuint Width, Height;
	//Texture format
	GLuint Internal_Format;    //format of texture object
	GLuint Image_Format;	      //format of loaded image
	//Texture configuration
	GLuint Wrap_S;
	GLuint Wrap_T;
	GLuint Filter_Min;
	GLuint Filter_Max;
	Texture2D();
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind() const;

private:

};


#endif // !TEXTURE_H
