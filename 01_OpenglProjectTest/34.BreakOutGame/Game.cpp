#include "Game.h"
#include "resource_manager.h"
#include "SpriteRenderer.h"   //渲染精灵
#include "BallObject.h"

SpriteRenderer *Renderer;
GameObject *Player;

//初始化小球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
//小球的半径
const GLfloat BALL_RADIUS = 12.5f;

//实例化小球
BallObject* Ball;

//实现构造函数
Game::Game(GLuint width, GLuint height):State(GAME_ACTIVE),Keys(),Width(width),Height(height)
{
	
}

Game::~Game()
{
	delete Renderer;    //释放内存
	delete Player;
}
void Game::Init()
{
	//加载shader
	ResourceManager::LoadShader("./../Assets/Shaders/Part4/BreakOut_Sprite.vert", "./../Assets/Shaders/Part4/BreakOut_Sprite.frag", nullptr, "sprite");

	//配置shader
	//正交投影
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);   //设置图片
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);   //设置投影方式

	//Load textures
	ResourceManager::LoadTexture("./../Assets/Textures/background.jpg", GL_FALSE, "background");  //添加backgrounds
	ResourceManager::LoadTexture("./../Assets/Textures/awesomeface.png", GL_TRUE, "face");  //在map容器里面添加texture
	ResourceManager::LoadTexture("./../Assets/Textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("./../Assets/Textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("./../Assets/Textures/paddle.png", true, "paddle");

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	//加载关卡
	GameLevel one;
	one.Load("./../Assets/Levels/one.lvl", this->Width, this->Height * 0.5f);
	GameLevel two;
	two.Load("./../Assets/Levels/two.lvl", this->Width, this->Height * 0.5f);
	GameLevel three;
	three.Load("./../Assets/Levels/three.lvl", this->Width, this->Height * 0.5f);
	GameLevel four;
	four.Load("./../Assets/Levels/four.lvl", this->Width, this->Height * 0.5f);
	//加载完成之后放在levels  vector容器中
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	//初始化level
	this->Level = 0;
	//初始化玩家信息
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	//初始化小球
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
}
//每帧进行调用
void Game::Update(GLfloat dt)
{
	Ball->Move(dt, this->Width);
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		//玩家的移动
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)      //左边屏幕的边缘
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
			if (Player->Position.x <= this->Width - Player->Size.x)    //右边屏幕的边缘
			{
				Player->Position.x += velocity;
				if (Ball->Stuck)
				{
					Ball->Position.x += velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])    //如果玩家按下了空格键
			Ball->Stuck = false;
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		//绘制背景
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		//绘制关卡
		this->Levels[this->Level].Draw(*Renderer);
		//绘制玩家
		Player->Draw(*Renderer);
		//绘制小球
		Ball->Draw(*Renderer);

	}
	/*Texture2D temple_texture2d = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(temple_texture2d, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));*/
}