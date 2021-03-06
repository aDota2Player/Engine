#pragma once

#define LONELY_INPUT

#include "Objects/GameObject.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"

#include "../Content/Maths.h"

#include "Graphics/ResourceManager/ResourceManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/Layer.h"
#include "Graphics/Particle/ParticleEmitter.h"

#include "Audio/SoundManager.h"
#include "Audio/Sound.h"

#include "App/Input.h"
#include "App/Window.h"

#include "FileReader.h"

#include <map>


using namespace lonely;
using namespace app;
using namespace graphics;
using namespace audio;
using namespace maths;
using namespace physics;


#define PADDLE_WIDTH				100.0f
#define PADDLE_HEIGHT				20.0f
#define PADDLE_VELOCITY				250.0


#define BALL_RADIUS					12.5f
#define BALL_INITIAL_VELOCITY_X		100.0f
#define BALL_INITIAL_VELOCITY_Y 	350.0f


class Game
{
private:
	enum GameState { GAME_ACTIVE, GAME_MENU, GAME_WIN };
	enum BallVertical { NONE, UP, DOWN };

	GameState m_State;
	Input m_Controller;

	mat4 m_Projection;
	unsigned int m_Width, m_Height;

	std::map<int, Layer*> m_Levels;
	unsigned int m_Level;

	Layer* m_PlayerLayer;
	Layer* m_BackgroundLayer;

	Ball* m_Ball;
	ParticleEmitter* m_ParticleEmitter;
	BallVertical m_BallVertical;
	double m_Motion;
	
	Paddle* m_Paddle;
	double m_PaddleVelocity;

	Sprite* m_Background;
	
public:

	Game(Window* window);

	~Game();

	void Init();

	void ProcessInput(double deltaTime);
	void Update(double deltaTime);
	void Render(double deltaTime);

private:
	void LoadLevel(std::string level_path, int index);

	void Reset();

};