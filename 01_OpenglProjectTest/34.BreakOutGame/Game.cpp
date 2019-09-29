#include "Game.h"
#include "resource_manager.h"
#include "SpriteRenderer.h"   //��Ⱦ����
#include "BallObject.h"
#include "ParticleGenerator.h"
#include "PostProcessor.h"

#include <algorithm>

SpriteRenderer *Renderer;
GameObject *Player;
//ʵ����С��
BallObject* Ball;
//��������
ParticleGenerator* Particles;
//����������Ч
PostProcessor* Effects;

GLfloat ShakeTime = 0.0f;

//��ʼ��С����ٶ�
//��һ������Ҫ�Ż�һ��
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
//С��İ뾶
const GLfloat BALL_RADIUS = 12.5f;

Collision CheckCollision(BallObject& one, GameObject& two);

Direction VectorDirection(glm::vec2 target);



//ʵ�ֹ��캯��
Game::Game(GLuint width, GLuint height):State(GAME_ACTIVE),Keys(),Width(width),Height(height)
{
	
}

Game::~Game()
{
	delete Renderer;    //�ͷ��ڴ�
	delete Player;
	delete Ball;
	delete Particles;
	delete Effects;
}

void Game::Init()
{
	//����shader
	ResourceManager::LoadShader("./../Assets/Shaders/Part4/BreakOut_Sprite.vert", "./../Assets/Shaders/Part4/BreakOut_Sprite.frag", nullptr, "sprite");
	//��������shader
	ResourceManager::LoadShader("./../Assets/Shaders/Part4/BreakOut_Particle.vert", "./../Assets/Shaders/Part4/BreakOut_Particle.frag", nullptr, "particle");
	//���غ���Ч��shader
	ResourceManager::LoadShader("./../Assets/Shaders/Part4/BreakOut_Post_Processing.vert", "./../Assets/Shaders/Part4/BreakOut_Post_Processing.frag", nullptr, "postprocessing");



	//����shader
	//����ͶӰ
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);   //����ͼƬ   /*����޸Ĺ�  image*/
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);   //����ͶӰ��ʽ
	//����
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);


	//Load textures
	ResourceManager::LoadTexture("./../Assets/Textures/background.jpg", GL_FALSE, "background");  //���backgrounds
	ResourceManager::LoadTexture("./../Assets/Textures/awesomeface.png", GL_TRUE, "face");  //��map�����������texture
	ResourceManager::LoadTexture("./../Assets/Textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("./../Assets/Textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("./../Assets/Textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("./../Assets/Textures/particle.png", GL_TRUE, "particle");    //����particle texture
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
	//С������ƶ�
	Ball->Move(dt, this->Width);
	//��ײ���
	this->DoCollisions();
	//��������ϵͳ
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2));
	//����Buff
	this->UpdatePowerUps(dt);

	//���ź�����Ч
	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0)
		{
			Effects->Shake = GL_FALSE;
		}
	}

	//�������Ƿ�ʧ��
	if (Ball->Position.y >= this->Height)
	{
		//���ùؿ������
		this->ResetLevel();
		this->ResetPlayer();
	}
}
//��ҵ�����
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
			Ball->Stuck = GL_FALSE;
	}
}
//��Ⱦ����
void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Effects->BeginRender();
		//���Ʊ���
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		//���ƹؿ�
		this->Levels[this->Level].Draw(*Renderer);
		//�������
		Player->Draw(*Renderer);
		//����buff
		for (PowerUp& powerUp:this->PowerUps )
		{
			if (!powerUp.Destoryed)
			{
				powerUp.Draw(*Renderer);
			}
		}

		//��������
		Particles->Draw();
		//����С��
		Ball->Draw(*Renderer);
		Effects->EndRender();
		Effects->Render(glfwGetTime());
	}
	/*Texture2D temple_texture2d = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(temple_texture2d, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));*/
}

//���ùؿ�
void Game::ResetLevel()
{
	//���ݵ�ǰ�ؿ������¼��عؿ�
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

//�������
void Game::ResetPlayer()
{
	//������Һ�С��λ�ú�״̬
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);   //�����м�
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

//�������õĴ���
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



//AABB��ײ�м�ⷽ��
GLboolean CheckCollision(GameObject& one, GameObject& two) 
{
	//AABB��ײ
	//x�᷽���Ƿ�������ײ
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x 
		&& two.Position.x + two.Size.x >= one.Position.x;
	//y�᷽���Ƿ�������ײ
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y
		&& two.Position.y + two.Size.y >= one.Position.y;
	//ֻ�������ᶼ������ײ��ʱ��ż����ײ
	return collisionX && collisionY;
}
//��ײ֮��Ҫ���еķ���
void Game::DoCollisions()
{
	for (GameObject& box: this->Levels[this->Level].Bricks )
	{
		if (!box.Destoryed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision))   //�����ײ��
			{
				//�������solid ������
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
				//��ײ�ض�λ
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (!(Ball->PassThrough && !box.IsSolid))
				{
					if (dir == LEFT || dir == RIGHT)
					{
						//��ת�ٶ�
						Ball->Velocity.x = -Ball->Velocity.x;
						//�ض�λ
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
					else   //��ֱ�任
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

	//�����pad�������ײ
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
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);   //x���෴
		Ball->Velocity.y = -1 * abs(Ball->Velocity.y);

		Ball->Stuck = Ball->Sticky;
	}
}
//AABB-Circle Collision
Collision CheckCollision(BallObject& one, GameObject& two)
{
	//AABB��ײ  ������ײ
	//��ȡԲ������
	glm::vec2 center(one.Position + one.Radius);
	//��ȡ����İ�߳�
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	//��ȡ���������
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	//����Բ�����뷽�����ĵľ���
	glm::vec2 difference = center - aabb_center;
	//�޶�ֵ
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	//AABB_center + clamped�͵õ�����ײ���Ͼ���Բ����ĵ�closest
	glm::vec2 closest = aabb_center + clamped;
	//�õ�Բ��center�������closest��ʸ�����ж��Ƿ�length<=radius
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

//������ײ֮����ķ���
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
