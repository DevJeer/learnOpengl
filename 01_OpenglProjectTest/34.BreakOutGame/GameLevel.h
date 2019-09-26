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
	//关卡状态
	std::vector<GameObject> Bricks;
	GameLevel() {}
	//加载关卡
	void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
	//绘制关卡
	void Draw(SpriteRenderer &renderer);
	//检测关卡是否结束
	GLboolean IsCompleted();

private:
	//初始化关卡
	void init(std::vector<std::vector<GLuint>>tileData, GLuint levelWidth, GLuint levelHeight);

};

#endif // !GAMELEVEL_H
