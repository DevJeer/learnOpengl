#pragma once
#ifndef GAME_H
#define GAME_H
#include <glew.1.9.0.1/build/native/include/GL/glew.h>
#include <glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	//GameState   
	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;
	Game(GLuint width, GLuint height);
	~Game();
	void Init();
	//Gameloop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

private:

};

#endif // !GAME_H
