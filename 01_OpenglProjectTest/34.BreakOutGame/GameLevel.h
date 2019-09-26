#pragma once
#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <glew-2.0.0/include/GL/glew.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "resource_manager.h"

class GameLevel
{
public:
	//�ؿ�״̬
	std::vector<GameObject> Bricks;
	GameLevel() {}
	//���عؿ�
	void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
	//���ƹؿ�
	void Draw(SpriteRenderer &renderer);
	//���ؿ��Ƿ����
	GLboolean IsCompleted();

private:
	//��ʼ���ؿ�
	void init(std::vector<std::vector<GLuint>>tileData, GLuint levelWidth, GLuint levelHeight);

};

#endif // !GAMELEVEL_H
