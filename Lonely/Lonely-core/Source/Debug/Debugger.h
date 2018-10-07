#include <GL/glew.h>

#include <iostream>
#include <string>

#include "Debug/ImGui/imgui.h"
#include "Debug/ImGui/imgui_impl_glfw_gl3.h"


#ifdef _DEBUG

#ifdef _WINDOWS_
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define GLC(x) lonely::debug::GLClearLog(); \
x; \
ASSERT(lonely::debug::GLLogCall(__LINE__, __FILENAME__, #x))

#define ASSERT(x) if(!(x)) __debugbreak();

#else

#define GLC(x) x

#define ASSERT(x) x

#endif

namespace lonely { namespace debug {

	static void GLClearLog();
	static bool GLLogCall(int line, const char* file, const char* function);
	static std::string GetErrorName(GLenum error);
	
} }



