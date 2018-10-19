#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debug/ImGui/imgui.h"
#include "Debug/ImGui/imgui_impl_glfw_gl3.h"

#include "Maths/vec2.h"

#include <string>
#include <iostream>
#include <functional>

#ifdef _DEBUG

#include <Windows.h>

#ifdef _WINDOWS_
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define GLC(x) lonely::Debugger::ClearErrors(); \
x; \
ASSERT(lonely::Debugger::LogCall(__LINE__, __FILENAME__, #x))

#define ASSERT(x) if(!(x)) __debugbreak();

#else

#define GLC(x) x

#define ASSERT(x) x

#endif

namespace lonely {

	class Debugger
	{
	protected:
		static std::string DebugWindowName;

	public:
		static void Initialize(GLFWwindow* window, std::function<void(ImGuiStyle* dst)> style,
			                  const std::string& debug_window_name,
			                  const maths::vec2& debug_window_position = maths::vec2(0.0f, 0.0f),
			                  bool install_callbacks = false);

		static void Begin();
		static void Render();

		static float GetFramerate();

		static void Destroy();

	protected:
		void ClearErrors();
		bool LogCall(int line, const char* file, const char* function);
		std::string GetErrorName(GLenum error);

		Debugger() {}
	};
}



