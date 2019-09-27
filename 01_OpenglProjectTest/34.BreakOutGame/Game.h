#pragma once
#ifndef GAME_H
#define GAME_H
#include <vector>

#include <glew-2.0.0/include/GL/glew.h>
#include <glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>

#include "GameLevel.h"   //��Ϸ�ؿ�

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

const glm::vec2 PLAYER_SIZE(100, 20);     //��ʼ����ҵĴ�С
const GLfloat PLAYER_VELOCITY(500.0f);  //��ʼ����ҵ��ƶ��ٶ�

class Game
{
public:
	//GameState   
	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;

	//�ؿ�
	std::vector<GameLevel> Levels;    //�ؿ�����
	GLuint Level;								    	//��ǰ�Ĺؿ�

	Game(GLuint width, GLuint height);
	~Game();
	void Init();
	//Gameloop
	void ProcessInput(GLfloat dt);  //��Ϸ�е�����
	void Update(GLfloat dt);
	void Render();   //��Ϸ�е���Ⱦ
	//��ײ֮��Ҫ��������
	void DoCollisions();

	//���ùؿ�
	void ResetLevel();
	void ResetPlayer();

private:

};

#endif // !GAME_H
