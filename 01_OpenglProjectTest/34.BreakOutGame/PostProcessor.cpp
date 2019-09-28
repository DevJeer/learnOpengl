#include "PostProcessor.h"

#include <iostream>

PostProcessor::PostProcessor(Shader shader, GLuint width, GLuint height) :
	PostProcessingShader(shader), Texture(), Width(width), Height(height), Confuse(GL_FALSE), Chaos(GL_FALSE), Shake(GL_FALSE)
{
	glGenFramebuffers(1, &this->MSFBO);
	glGenFramebuffers(1, &this->FBO);
	glGenRenderbuffers(1, &this->RBO);

	glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, width, height);
}