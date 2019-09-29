#include "Game.h"
#include "resource_manager.h"
#include "SpriteRenderer.h"   //渲染精灵
#include "BallObject.h"
#include "ParticleGenerator.h"
#include "PostProcessor.h"

#include <algorithm>

SpriteRenderer *Renderer;
GameObject *Player;
//实例化小球
BallObject* Ball;
//创建粒子
ParticleGenerator* Particles;
//创建后期特效
PostProcessor* Effects;

GLfloat ShakeTime = 0.0f;

//初始化小球的速度
//这一部分需要优化一下
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
//小球的半径
const GLfloat BALL_RADIUS = 12.5f;

Collision CheckCollision(BallObject& one, GameObject& two);

Direction VectorDirection(glm::vec2 target);



//实现构造函数
Game::Game(GLuint width, GLuint height):State(GAME_ACTIVE),Keys(),Width(width),Height(height)
{
	
}

Game::~Game()
{
	delete Renderer;    //释放内存
	delete Player;
	delete Ball;
	delete Particles;
	delete Effects;
}

void Game::Init()
{
	//加载shader
	ResourceManager::LoadShader("./../Assets/Shaders/Part4/BreakOut_Sprite.vert", "./../Assets/Shaders/Part4/BreakOut_Sprite.frag", nullptr, "sprite");
	//加载粒子shader
	ResourceManager::LoadShader("./../Assets/Shaders/Part4/BreakOut_Particle.vert", "./../Assets/Shaders/Part4/BreakOut_Particle.frag", nullptr, "particle");
	//加载后期效果shader
	ResourceManager::LoadShader("./../Assets/Shaders/Part4/BreakOut_Post_Processing.vert", "./../Assets/Shaders/Part4/BreakOut_Post_Processing.frag", nullptr, "postprocessing");



	//配置shader
	//正交投影
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);   //设置图片   /*这儿修改过  image*/
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);   //设置投影方式
	//粒子
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);


	//Load textures
	ResourceManager::LoadTexture("./../Assets/Textures/background.jpg", GL_FALSE, "background");  //添加backgrounds
	ResourceManager::LoadTexture("./../Assets/Textures/awesomeface.png", GL_TRUE, "face");  //在map容器里面添加texture
	ResourceManager::LoadTexture("./../Assets/Textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("./../Assets/Textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("./../Assets/Textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("./../Assets/Textures/particle.png", GL_TRUE, "particle");    //加载particle texture
	//Load PowerUps
	ResourceManager::LoadTexture("./../Assets/Textures/powerup_speed.png", GL_TRUE, "powerup_speed");
	ResourceManager::LoadTexture("./../Assets/Textures/powerup_sticky.png", GL_TRUE, "powerup_sticky");
	ResourceManager::LoadTexture("./../Assets/Textures/powerup_increase.png", GL_TRUE, "powerup_increase");
	ResourceManager::LoadTexture("./../Assets/Textures/powerup_confuse.png", GL_TRUE, "powerup_confuse");
	ResourceManager::LoadTexture("./../Assets/Textures/powerup_chaos.png", GL_TRUE, "powerup_chaos");
	ResourceManager::LoadTexture("./../Assets/Textures/powerup_passthrough.png", GL_TRUE, "powerup_passthrough");

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);
	Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);

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
	//小球进行移动
	Ball->Move(dt, this->Width);
	//碰撞检测
	this->DoCollisions();
	//更新粒子系统
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2));
	//更新Buff
	this->UpdatePowerUps(dt);

	//播放后期特效
	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0)
		{
			Effects->Shake = GL_FALSE;
		}
	}

	//检查玩家是否失败
	if (Ball->Position.y >= this->Height)
	{
		//重置关卡和玩家
		this->ResetLevel();
		this->ResetPlayer();
	}
}
//玩家的输入
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
			Ball->Stuck = GL_FALSE;
	}
}
//渲染场景
void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Effects->BeginRender();
		//绘制背景
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		//绘制关卡
		this->Levels[this->Level].Draw(*Renderer);
		//绘制玩家
		Player->Draw(*Renderer);
		//绘制buff
		for (PowerUp& powerUp:this->PowerUps )
		{
			if (!powerUp.Destoryed)
			{
				powerUp.Draw(*Renderer);
			}
		}

		//绘制粒子
		Particles->Draw();
		//绘制小球
		Ball->Draw(*Renderer);
		Effects->EndRender();
		Effects->Render(glfwGetTime());
	}
	/*Texture2D temple_texture2d = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(temple_texture2d, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));*/
}

//重置关卡
void Game::ResetLevel()
{
	//根据当前关卡数重新加载关卡
	if (this->Level == 0)
	{ 
		this->Levels[0].Load("./../Assets/Levels/one.lvl", this->Width, this->Height * 0.5f);
	}
	else if (this->Level == 1)
	{
		this->Levels[1].Load("./../Assets/Levels/two.lvl", this->Width, this->Height * 0.5f);
	}
	else if (this->Level == 2)
	{
		this->Levels[2].Load("./../Assets/Levels/three.lvl", this->Width, this->Height * 0.5f);
	}
	else if (this->Level == 3)
	{
		this->Levels[3].Load("./../Assets/Levels/four.lvl", this->Width, this->Height * 0.5f);
	}
}

//重置玩家
void Game::ResetPlayer()
{
	//重置玩家和小球位置和状态
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);   //底下中间
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);

	Effects->Chaos = Effects->Confuse = GL_FALSE;
	Ball->PassThrough = Ball->Sticky = GL_FALSE;
	Player->Color = glm::vec3(1.0f);
	Ball->Color = glm::vec3(1.0f);
}
//buff
GLboolean IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type);

void Game::UpdatePowerUps(GLfloat dt)
{
	for (PowerUp& powerUp : this->PowerUps)
	{
		powerUp.Position += powerUp.Velocity * dt;
		if (powerUp.Activated)
		{
			powerUp.Duration -= dt;
			if (powerUp.Duration <= 0.0f)
			{
				powerUp.Activated = GL_FALSE;
				if (powerUp.Type == "sticky")
				{	
					if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
					{
						Ball->Sticky = GL_FALSE;
						Ball->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "pass-through")
				{
					if(!IsOtherPowerUpActive(this->PowerUps,"pass-through"))
					{
						Ball->PassThrough = GL_FALSE;
						Ball->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "confuse")
				{
					if (!IsOtherPowerUpActive(this->PowerUps,"confuse"))
					{
						Effects->Confuse = GL_FALSE;
					}
				}
				else if (powerUp.Type == "chaos")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
					{
						Effects->Chaos = GL_FALSE;
					}
				}
			}
		}
	}
	this->PowerUps.erase(std::remove_if(this->PowerUps.begin(),this->PowerUps.end(),
		[](const PowerUp& powerUp) {return powerUp.Destoryed && !powerUp.Activated; }
	), this->PowerUps.end());

}

GLboolean ShouldSpawn(GLuint chance)
{
	GLuint random = rand() % chance;
	return random == 0;
}

void Game::SpawnPowerUps(GameObject& block)
{
	if (ShouldSpawn(10))
		this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
	if (ShouldSpawn(10))
	{
		this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
	}
	if (ShouldSpawn(10))
	{
		this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
	}
	if (ShouldSpawn(10))
	{
		this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
	}
	if (ShouldSpawn(15))
	{
		this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
	}
	if (ShouldSpawn(15))
	{
		this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
	}
}

//道具作用的触发
void ActivatePowerUp(PowerUp& powerUp)
{
	if (powerUp.Type == "speed")
	{
		Ball->Velocity *= 1.2f;
	}
	else if (powerUp.Type == "sticky")
	{
		Ball->Sticky = GL_TRUE;
		Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
	}
	else if (powerUp.Type == "pass-through")
	{
		Ball->PassThrough = GL_TRUE;
		Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
	}
	else if (powerUp.Type == "pad-size-increase")
	{
		Player->Size.x += 50;
	}
	else if (powerUp.Type == "confuse")
	{
		if (!Effects->Chaos)
		{
			Effects->Confuse = GL_TRUE;
		}
	}
	else if (powerUp.Type == "chaos")
	{
		if (!Effects->Confuse)
		{
			Effects->Chaos = GL_TRUE;
		}
	}
}

GLboolean IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
{
	for (const PowerUp& powerUp:powerUps)
	{
		if (powerUp.Activated)
		{
			if (powerUp.Type == type)
			{
				return GL_TRUE;
			}
		}
	}
	return GL_FALSE;
}



//AABB碰撞盒检测方法
GLboolean CheckCollision(GameObject& one, GameObject& two) 
{
	//AABB碰撞
	//x轴方向是否发生了碰撞
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x 
		&& two.Position.x + two.Size.x >= one.Position.x;
	//y轴方向是否发生了碰撞
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y
		&& two.Position.y + two.Size.y >= one.Position.y;
	//只有两个轴都发生碰撞的时候才检测碰撞
	return collisionX && collisionY;
}
//碰撞之后要进行的方法
void Game::DoCollisions()
{
	for (GameObject& box: this->Levels[this->Level].Bricks )
	{
		if (!box.Destoryed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision))   //如果碰撞了
			{
				//如果不是solid 就销毁
				if (!box.IsSolid)
				{
					box.Destoryed = GL_TRUE;
					this->SpawnPowerUps(box);
				}
				else
				{
					ShakeTime = 0.05f;
					Effects->Shake = GL_TRUE;
				}
				//碰撞重定位
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (!(Ball->PassThrough && !box.IsSolid))
				{
					if (dir == LEFT || dir == RIGHT)
					{
						//翻转速度
						Ball->Velocity.x = -Ball->Velocity.x;
						//重定位
						GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
						if (dir == LEFT)
						{
							Ball->Position.x += penetration;
						}
						else
						{
							Ball->Position.x -= penetration;
						}
					}
					else   //垂直变换
					{
						Ball->Velocity.y = -Ball->Velocity.y;

						GLfloat penetartion = Ball->Radius - std::abs(diff_vector.y);
						if (dir == UP)
						{
							Ball->Position.y -= penetartion;
						}
						else
						{
							Ball->Position.y += penetartion;
						}
					}
				
				}
				
			}

		}
	}

	for (PowerUp& powerUp : this->PowerUps)
	{
		if (!powerUp.Destoryed)
		{
			if (powerUp.Position.y >= this->Height)
			{
				powerUp.Destoryed = GL_TRUE;
			}
			if (CheckCollision(*Player, powerUp))
			{
				ActivatePowerUp(powerUp);
				powerUp.Destoryed = GL_TRUE;
				powerUp.Activated = GL_TRUE;
			}
		}
	}

	//检测在pad上面的碰撞
	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
		GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		GLfloat percentage = distance / (Player->Size.x / 2);

		//Move
		GLfloat strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);   //x轴相反
		Ball->Velocity.y = -1 * abs(Ball->Velocity.y);

		Ball->Stuck = Ball->Sticky;
	}
}
//AABB-Circle Collision
Collision CheckCollision(BallObject& one, GameObject& two)
{
	//AABB碰撞  球形碰撞
	//获取圆的中心
	glm::vec2 center(one.Position + one.Radius);
	//获取方块的半边长
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	//获取方块的中心
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	//计算圆中心与方块中心的距离
	glm::vec2 difference = center - aabb_center;
	//限定值
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	//AABB_center + clamped就得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	//得到圆心center和最近点closest的矢量并判断是否length<=radius
	difference = closest - center;

	if (glm::length(difference) < one.Radius)
	{
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	}
	else
	{
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
	}
}

//计算碰撞之后朝向的方向
Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] =
	{
		glm::vec2(0.0f,1.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(0.0f,-1.0f),
		glm::vec2(-1.0f,0.0f)
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}

	return (Direction)best_match;
}
