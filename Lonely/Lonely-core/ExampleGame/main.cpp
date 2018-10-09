
#define LONLEY_INPUT
#include "App/Window.h"

#include "Maths.h"

#include "Game.h"
#include "Timer.h"

#include "Audio/SoundManager.h"

Window window(810, 600, "Lonely-Breakout", 0, false);
Game Breakout(&window);

Timer timer;
DeltaTimer deltatime;


unsigned int frames;

int main()
{
	Breakout.Init();

	// todo: make a class to handle OpenGL's blending stuff
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	timer.reset();

	Framebuffer buffer(window.GetWidth(), window.GetHeight(), ResourceManager::LoadShader("framebuffer", "ExampleGame/framebuffer.vs", "ExampleGame/framebuffer.fs"));

	while (!window.Closed())
	{
		deltatime.Update();
		window.Clear();


		Breakout.ProcessInput(deltatime.GetDeltaTime());
		Breakout.Update      (deltatime.GetDeltaTime());

		buffer.Begin();
		Breakout.Render                              ();
		buffer.End();
		buffer.Draw(false);

		window.Update();	
		
		frames++;
		if (timer.elapsed() - 1.0f >= 0.0f)
		{
			timer.reset();

			printf("FPS: %d\n", frames);
			frames = 0;
		}
	}	
}