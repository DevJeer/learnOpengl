#pragma once
#ifndef GAME_H
#define GAME_H
#include <vector>

#include <glew-2.0.0/include/GL/glew.h>
#include <glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>

#include "GameLevel.h"   //游戏关卡

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

const glm::vec2 PLAYER_SIZE(100, 20);     //初始化玩家的大小
const GLfloat PLAYER_VELOCITY(500.0f);  //初始化玩家的移动速度

class Game
{
public:
	//GameState   
	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;

	//关卡
	std::vector<GameLevel> Levels;    //关卡集合
	GLuint Level;								    	//当前的关卡

	Game(GLuint width, GLuint height);
	~Game();
	void Init();
	//Gameloop
	void ProcessInput(GLfloat dt);  //游戏中的输入
	void Update(GLfloat dt);
	void Render();   //游戏中的渲染
	//碰撞之后要做的事情
	void DoCollisions();

	//重置关卡
	void ResetLevel();
	void ResetPlayer();

private:

};

#endif // !GAME_H
