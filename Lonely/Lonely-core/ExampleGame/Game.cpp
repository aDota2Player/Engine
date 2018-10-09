#include "Game.h"


Game::Game(Window* window)
{
	m_Width = window->GetWidth();
	m_Height = window->GetHeight();
	window->AttachController(&m_Controller);

	m_BallVertical = BallVertical::UP;
}

Game::~Game() 
{
	delete m_Ball;
	delete m_Paddle;
	delete m_Background;
}

void Game::Init()
{
	SoundManager::Initialize();

	SoundManager::LoadSound("background",     "ExampleGame/Resources/Audio/background.ogg");
	SoundManager::LoadSound("ball_non-solid", "ExampleGame/Resources/Audio/ball_non-solid.ogg");
	SoundManager::LoadSound("ball_solid",     "ExampleGame/Resources/Audio/ball_solid.ogg");
	SoundManager::LoadSound("ball_paddle",    "ExampleGame/Resources/Audio/ball_paddle.ogg");


	ResourceManager::LoadShader("sprite", "ExampleGame/Resources/Shaders/sprite.vs", "ExampleGame/Resources/Shaders/sprite.fs");

	ResourceManager::LoadTexture("block_solid", "ExampleGame/Resources/Textures/block_solid.png");
	ResourceManager::LoadTexture("block", "ExampleGame/Resources/Textures/block.png");
	ResourceManager::LoadTexture("ball", "ExampleGame/Resources/Textures/awesomeface.png", false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	ResourceManager::LoadTexture("paddle", "ExampleGame/Resources/Textures/paddle.png");
	ResourceManager::LoadTexture("background", "ExampleGame/Resources/Textures/background.jpg");

	m_Projection = mat4::Orthographic(0.0f, m_Width, m_Height, 0.0f, 1.0f, -1.0f);

	m_Background = new Sprite(maths::vec2(0.0f, 0.0f), maths::vec2(m_Width, m_Height), ResourceManager::GetTexture("background"));

	m_Paddle = new Paddle((m_Width / 2.0f) - (PADDLE_WIDTH / 2.0f), m_Height - PADDLE_HEIGHT,
		                  PADDLE_WIDTH, PADDLE_HEIGHT,
		                  PADDLE_VELOCITY,
		                  ResourceManager::GetTexture("paddle"));
	m_Ball = new Ball((m_Width / 2.0f) - (BALL_RADIUS), m_Height - (PADDLE_HEIGHT + BALL_RADIUS * 2), BALL_RADIUS,
					  BALL_INITIAL_VELOCITY_X, BALL_INITIAL_VELOCITY_Y,
		              ResourceManager::GetTexture("ball"));

	Reset();

	LoadLevel("ExampleGame/Resources/Levels/One.txt", 0);
	LoadLevel("ExampleGame/Resources/Levels/Two.txt", 1);
	LoadLevel("ExampleGame/Resources/Levels/Three.txt", 2);
	LoadLevel("ExampleGame/Resources/Levels/Four.txt", 3);
	m_Level = 0;

	SoundManager::GetSound("background")->Play(true);
}

void Game::ProcessInput(double deltaTime)
{
	if (m_Controller.GetKey(KEY_1))
		m_Level = 0;

	if (m_Controller.GetKey(KEY_2))
		m_Level = 1;

	if (m_Controller.GetKey(KEY_3))
		m_Level = 2;

	if (m_Controller.GetKey(KEY_4))
		m_Level = 3;

	m_PaddleVelocity = deltaTime * m_Paddle->GetSpeed();

	if (m_Controller.GetKey(KEY_A))
	{
		m_Paddle->SetX(m_Paddle->GetX() - m_PaddleVelocity);
		
		if (m_Ball->stuck)
			m_Ball->SetX(m_Ball->GetX() - m_PaddleVelocity);
	}

	if (m_Controller.GetKey(KEY_D))
	{
		m_Paddle->SetX(m_Paddle->GetX() + m_PaddleVelocity);

		if (m_Ball->stuck)
			m_Ball->SetX(m_Ball->GetX() + m_PaddleVelocity);
	}

	if (m_Controller.GetKey(KEY_R))
		Reset();

	if (m_Controller.GetKey(KEY_SPACE))
		m_Ball->stuck = false;
}

void Game::Update(double deltaTime)
{
	if (m_Paddle->GetX() > m_Width - PADDLE_WIDTH)
	{
		m_Paddle->SetX(m_Width - PADDLE_WIDTH);
		if (m_Ball->stuck)
			m_Ball->SetX(m_Ball->GetX() - m_PaddleVelocity);
	}

	if (m_Paddle->GetX() < 0)
	{
		m_Paddle->SetX(0);
		if (m_Ball->stuck)
			m_Ball->SetX(m_Ball->GetX() + m_PaddleVelocity);
	}


	if (!m_Ball->stuck)
	{
		if (m_Ball->GetX() < 0)
			m_Ball->velocity.x = std::abs(m_Ball->velocity.x);

		if (m_Ball->GetX() > m_Width - m_Ball->collision.radius * 2)
			m_Ball->velocity.x = -1.0f * std::abs(m_Ball->velocity.x);
		
		if (m_Ball->GetY() < 0)
			m_BallVertical = BallVertical::DOWN;

		for (auto& sprite : m_Levels[m_Level]->GetSprites())
		{
			GameObject* object = (GameObject*)sprite;
		
			if (m_Ball->collision.Intersects(object->collision) && !object->Destroyed()
				&& object != (GameObject*)m_Ball && object != (GameObject*)m_Paddle)
			{
				Direction dir = m_Ball->collision.Collided(object->collision);

				if (dir == Direction::UP)
					m_BallVertical = BallVertical::UP;
				
				if (dir == Direction::DOWN)
					m_BallVertical = BallVertical::DOWN;

				if (dir == Direction::LEFT)
					m_Ball->velocity.x = -1.0f * std::abs(m_Ball->velocity.x);
				
				if (dir == Direction::RIGHT)
					m_Ball->velocity.x = std::abs(m_Ball->velocity.x);


				if (!object->isSolid())
				{
					object->Destroy();
					SoundManager::GetSound("ball_non-solid")->Play(false, true);
				}
				else
					SoundManager::GetSound("ball_solid")->Play(false, true);
			}
		}

		if (m_Ball->collision.Intersects(m_Paddle->collision))
		{
			SoundManager::GetSound("ball_paddle")->Play(false, true);

			float center = m_Paddle->GetPosition().x + m_Paddle->GetSize().x / 2.0f;
			float distance = (m_Ball->GetPosition().x + m_Ball->collision.radius) - center;
			float percentage = distance / (m_Paddle->GetSize().x / 2.0f);

			float strength = 2.0f;
		
			m_Ball->velocity.x = BALL_INITIAL_VELOCITY_X * percentage * strength;
			m_BallVertical = BallVertical::UP;
		}

		m_Motion = glfwGetTime();
		
		if (m_BallVertical == BallVertical::UP)
			m_Ball->velocity.y = -1.0f * std::abs(BALL_INITIAL_VELOCITY_Y + m_Motion);
		else
			m_Ball->velocity.y = std::abs(BALL_INITIAL_VELOCITY_Y + m_Motion);

		m_Ball->SetPosition(m_Ball->GetPosition() + maths::vec2(m_Ball->velocity.x, m_Ball->velocity.y) * deltaTime);
	}
}

void Game::Render()
{
	m_Levels[m_Level]->Bind();
	m_Levels[m_Level]->Render();
	m_Levels[m_Level]->UnBind();
}

void Game::Reset()
{
	m_Paddle->SetPosition(maths::vec2( (m_Width / 2.0f) - (PADDLE_WIDTH / 2.0f), m_Height - PADDLE_HEIGHT));

	m_Ball->SetPosition(maths::vec2((m_Width / 2.0f) - (BALL_RADIUS), m_Height - (PADDLE_HEIGHT + BALL_RADIUS * 2)));
	m_Ball->velocity.x = BALL_INITIAL_VELOCITY_X;
	m_Ball->velocity.y = BALL_INITIAL_VELOCITY_Y + m_Motion;
	m_Ball->stuck = true;
}

void Game::LoadLevel(std::string level_path, int index)
{
	m_Levels[index] = new Layer(ResourceManager::GetShader("sprite"), m_Projection);

	m_Levels[index]->Add(m_Background);
	m_Levels[index]->Add(m_Paddle);

	std::string file = FileToString(level_path);

	std::vector<std::vector<char>> tiles;
	std::vector<char> row;

	unsigned int columns = 0;
	unsigned int rows = 0;

	for (const auto& c : file)
	{
		if (c == '\n')
			break;
		if (c != ' ')
			columns++;
	}

	for (const auto& c : file)
		if (c == '\n')
			rows++;

	for (const auto& c : file)
	{
		if (c == '\n')
		{
			tiles.push_back(row);
			row.clear();
			continue;
		}
		if (c != ' ')
			row.push_back(c);
	}

	unsigned int y = 0, x = 0;
	float unit_width = m_Width / columns;
	float unit_height = m_Height / 2 / rows;

	maths::vec4 color;
	bool solid = false;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			if (tiles[y][x] == '0')
				continue;

			if (tiles[y][x] == '1')
			{
				color = maths::vec4(0.8f, 0.8f, 0.7f, 1.0f);
				solid = true;
				m_Levels[index]->Add(new GameObject(x * unit_width, y * unit_height, unit_width, unit_height, true,
					ResourceManager::GetTexture("block_solid"), color));
				continue;
			}

			if (tiles[y][x] == '2')
				color = maths::vec4(0.2f, 0.6f, 1.0f, 1.0f);

			if (tiles[y][x] == '3')
				color = maths::vec4(0.0f, 0.7f, 0.0f, 1.0f);
			if (tiles[y][x] == '4')
				color = maths::vec4(0.8f, 0.8f, 0.4f, 1.0f);
			if (tiles[y][x] == '5')
				color = maths::vec4(1.0f, 0.5f, 0.0f, 1.0f);

			m_Levels[index]->Add(new GameObject(x * unit_width, y * unit_height, unit_width, unit_height, false,
				ResourceManager::GetTexture("block"), color));
		}
	}
	m_Levels[index]->Add(m_Ball);
}
