#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glew-2.0.0/include/GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	//Object state
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation;
	GLboolean IsSolid;
	GLboolean Destoryed;

	//Render state
	Texture2D Sprite;

	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	//���ƾ���
	virtual void Draw(SpriteRenderer &renderer);
	
private:

};




#endif // !GAMEOBJECT_H
