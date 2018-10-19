#include "Debugger.h"

#include <GLFW/glfw3.h>

namespace lonely {

	std::string Debugger::DebugWindowName;

	void Debugger::Initialize(GLFWwindow* window, std::function<void(ImGuiStyle* dst)> style,
		                      const std::string& debug_window_name,
		                      const maths::vec2& debug_window_position  /*= maths::vec2(0.0f, 0.0f)*/,
		                      bool install_callbacks /*= false*/)
	{
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, install_callbacks);
		DebugWindowName = debug_window_name.c_str();

		style(0);

		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::SetNextWindowPos(ImVec2(debug_window_position.x, debug_window_position.y));
		ImGui::Begin(DebugWindowName.c_str());
		ImGui::End();
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Debugger::Begin()
	{
		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::Begin(DebugWindowName.c_str());
	}

	void Debugger::Render()
	{
		ImGui::End();
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	float Debugger::GetFramerate()
	{
		return ImGui::GetIO().Framerate;
	}

	void Debugger::Destroy()
	{
		ImGui::DestroyContext();
	}


	void Debugger::ClearErrors()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool Debugger::LogCall(int line, const char* file, const char* function)
	{
		if (GLenum error = glGetError())
		{
			std::cout 
				<< "[ OpenGL ERROR ]: file: "	<< file 
				<< " | line: "					<< line 
				<< " | error: "					<< GetErrorName(error) 
				<< " | function: "				<< function  
				<< std::endl;
			return false;
		}
		return true;
	}

	std::string Debugger::GetErrorName(GLenum error)
	{
		switch (error)
		{
		case GL_INVALID_ENUM:					return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE:					return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION:				return "GL_INVALID_OPERATION";
		case GL_STACK_OVERFLOW:					return "GL_STACK_OVERFLOW";
		case GL_STACK_UNDERFLOW:				return "GL_STACK_UNDERFLOW";
		case GL_OUT_OF_MEMORY:					return "GL_OUT_OF_MEMORY";
		case GL_INVALID_FRAMEBUFFER_OPERATION:	return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_CONTEXT_LOST:					return "GL_CONTEXT_LOST";
		case GL_TABLE_TOO_LARGE:				return "GL_TABLE_TOO_LARGE";
		default:								return "unknown";
		}
	}

}


