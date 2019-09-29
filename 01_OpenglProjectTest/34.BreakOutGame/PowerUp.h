#pragma once
#ifndef POWER_UP_H
#define POWER_UP_H

#include <string>
#include <glew-2.0.0/include/GL/glew.h>
#include <glm/glm.hpp>
#include "GameObject.h"
//道具的大小
const glm::vec2 SIZE(60, 20);
//道具下降的速度
const glm::vec2 VELOCITY(0.0f, 150.0f);

class PowerUp:public GameObject
{
public:
	std::string Type;
	GLfloat Duration;
	GLboolean Activated =GL_FALSE;
	PowerUp(std::string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture) :
		GameObject(position, SIZE, texture, color, VELOCITY), Type(type), Duration(duration), Activated()
	{
		
	}
private:

};

#endif // !POWER_UP_H
