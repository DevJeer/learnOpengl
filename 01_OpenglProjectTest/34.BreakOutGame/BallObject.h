#pragma once
#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glew-2.0.0/include/GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

//�����̳���GameObject��
class BallObject: public GameObject
{
public:
	//���״̬
	GLfloat Radius;   //��İ뾶
	GLboolean Stuck;   //���Ƿ��ڵ�����

	BallObject();
	//С��ĺ��ι��캯��
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
	//С���ƶ��ķ���
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	//����λ��
	void Reset(glm::vec2 position, glm::vec2 velocity);

private:

};

#endif // !BALLOBJECT_H
