#include "Game.h"

#include "Timer.h"
#include "Debug/Debugger.h"

Window window(810, 600, "Lonely-Breakout", 0, false);
Game breakout(&window);
Timer timer;

int main()
{
	breakout.Init();
	Debugger::Initialize(window.GetWindowPointer(), ImGui::StyleColorsDark, "DebugWindow");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!window.isClosed())
	{
		timer.Update();
		window.Clear();

		breakout.ProcessInput(timer.DeltaTime());
		breakout.Update(timer.DeltaTime());
		breakout.Render(timer.DeltaTime());

		{
			Debugger::Begin();
			
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / Debugger::GetFramerate(), Debugger::GetFramerate());
			ImGui::Text("DeltaTime: %f ", timer.DeltaTime());
			ImGui::Text("ElapsedTime: %f ", timer.ElapsedTime());

			Debugger::Render();
		}

		window.Update();
	}
	window.~Window();
	Debugger::Destroy();
}