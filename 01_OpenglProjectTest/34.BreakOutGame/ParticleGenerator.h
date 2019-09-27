#pragma once
#ifndef PARTILE_GENERATOR_H
#define PARTILE_GENERATOR_H
#include <vector>
#include <glew-2.0.0/include/GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

struct Particle
{
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle() :Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) {}
};

class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader,Texture2D texture,GLuint amount);
	//更新所有粒子
	void Update(GLfloat dt, GameObject& object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	//渲染所有粒子
	void Draw();

private:
	//State
	std::vector<Particle> particles;
	GLuint amount;
	//Render state
	Shader shader;
	Texture2D texture;
	GLuint VAO;
	//初始化Buffer和顶点数据
	void Init();

	GLuint firstUnusedParticle();
	//重新生成粒子
	void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

};

#endif // !PARTILE_GENERATOR_H
