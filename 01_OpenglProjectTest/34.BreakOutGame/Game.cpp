#include "Game.h"
#include "resource_manager.h"
#include "SpriteRenderer.h"   //��Ⱦ����
#include "BallObject.h"

SpriteRenderer *Renderer;
GameObject *Player;

//��ʼ��С����ٶ�
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
//С��İ뾶
const GLfloat BALL_RADIUS = 12.5f;

//ʵ����С��
BallObject* Ball;

//ʵ�ֹ��캯��
Game::Game(GLuint width, GLuint height):State(GAME_ACTIVE),Keys(),Width(width),Height(height)
{
	
}

Game::~Game()
{
	delete Renderer;    //�ͷ��ڴ�
	delete Player;
}
void Game::Init()
{
	//����shader
	ResourceManager::LoadShader("./../Assets/Shaders/Part4/BreakOut_Sprite.vert", "./../Assets/Shaders/Part4/BreakOut_Sprite.frag", nullptr, "sprite");

	//����shader
	//����ͶӰ
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);   //����ͼƬ
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);   //����ͶӰ��ʽ

	//Load textures
	ResourceManager::LoadTexture("./../Assets/Textures/background.jpg", GL_FALSE, "background");  //���backgrounds
	ResourceManager::LoadTexture("./../Assets/Textures/awesomeface.png", GL_TRUE, "face");  //��map�����������texture
	ResourceManager::LoadTexture("./../Assets/Textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("./../Assets/Textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("./../Assets/Textures/paddle.png", true, "paddle");

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	//���عؿ�
	GameLevel one;
	one.Load("./../Assets/Levels/one.lvl", this->Width, this->Height * 0.5f);
	GameLevel two;
	two.Load("./../Assets/Levels/two.lvl", this->Width, this->Height * 0.5f);
	GameLevel three;
	three.Load("./../Assets/Levels/three.lvl", this->Width, this->Height * 0.5f);
	GameLevel four;
	four.Load("./../Assets/Levels/four.lvl", this->Width, this->Height * 0.5f);
	//�������֮�����levels  vector������
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	//��ʼ��level
	this->Level = 0;
	//��ʼ�������Ϣ
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	//��ʼ��С��
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
}
//ÿ֡���е���
void Game::Update(GLfloat dt)
{
	Ball->Move(dt, this->Width);
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		//��ҵ��ƶ�
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)      //�����Ļ�ı�Ե
			{
				Player->Position.x -= velocity;
				if (Ball->Stuck)
				{
					Ball->Position.x -= velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)    //�ұ���Ļ�ı�Ե
			{
				Player->Position.x += velocity;
				if (Ball->Stuck)
				{
					Ball->Position.x += velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])    //�����Ұ����˿ո��
			Ball->Stuck = false;
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		//���Ʊ���
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		//���ƹؿ�
		this->Levels[this->Level].Draw(*Renderer);
		//�������
		Player->Draw(*Renderer);
		//����С��
		Ball->Draw(*Renderer);

	}
	/*Texture2D temple_texture2d = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(temple_texture2d, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));*/
}