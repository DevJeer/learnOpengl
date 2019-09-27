#pragma once
#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <glew-2.0.0/include/GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"
#include "Shader.h"

class PostProcessor
{
public:
	Shader PostProcessingShader;
	Texture2D Texture;
	GLuint Width, Height;
	//Ñ¡Ôñ
	GLboolean Confuse, Chaos, Shake;
	PostProcessor(Shader shader, GLuint width, GLuint height);

	void BeginRender();

	void EndRender();

	void Render(GLfloat time);

private:
	GLuint MSFBO, FBO;
	GLuint RBO;
	GLuint VAO;

	void initRenderData();

};


#endif // !POST_PROCESSOR_H
