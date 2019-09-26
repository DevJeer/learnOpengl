#pragma once
#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glew-2.0.0/include/GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

//球的类继承自GameObject类
class BallObject: public GameObject
{
public:
	//球的状态
	GLfloat Radius;   //球的半径
	GLboolean Stuck;   //球是否在挡板上

	BallObject();
	//小球的含参构造函数
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
	//小球移动的方法
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	//重置位置
	void Reset(glm::vec2 position, glm::vec2 velocity);

private:

};

#endif // !BALLOBJECT_H
