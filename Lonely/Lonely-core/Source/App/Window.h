#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define LONELY_DEFAULT_WINDOW_WIDTH		800
#define LONELY_DEFAULT_WINDOW_HEIGHT	600
#define LONELY_DEFAULT_WINDOW_TITLE    "Lonely"


namespace lonely { namespace graphics { class Framebuffer; } }

namespace lonely { namespace app {

	class Input;

	class Window
	{
	private:
		friend class Input;

		// Window
		GLFWwindow* m_Window;
		unsigned int m_Width, m_Height;
		char* m_Title;
		bool b_FullScreen;

		graphics::Framebuffer* m_Framebuffer;
		// Input
		Input* m_Controller;

	public:
		Window();
		Window(unsigned int width, unsigned int height, char* title, unsigned int glfw_samples = 0, bool full_screen = false);
		
	    ~Window();
	
		void Clear();
		void ClearColor(float r, float g, float b);
		void Update();

		// Setters
		// ----------------------------------------------------------------------------
		
		inline void Close() { glfwSetWindowShouldClose(m_Window, true); }
		
		inline void AttachController(Input* input) { m_Controller = input; }

		inline void SetFramebuffer(graphics::Framebuffer* buffer) {                m_Framebuffer = buffer;      }
		inline void SetTitle      (    char* title    ) { m_Title = title; glfwSetWindowTitle(m_Window, title); }

		// Getters
		// ----------------------------------------------------------------------------

		// Window
		inline unsigned int GetWidth () const {                   return m_Width ;                   }
		inline unsigned int GetHeight() const {                   return m_Height;                   }
		inline bool	        isClosed () const { return glfwWindowShouldClose(m_Window) == GLFW_TRUE; }
		
		inline char*        GetTitle() const  {                   return m_Title ;                   }

		inline			 GLFWwindow * GetWindowPointer()  { return m_Window;      }
		inline graphics::Framebuffer* GetFramebuffer  ()  { return m_Framebuffer; }

	private:
		bool Initialize(unsigned int samples); // Called in constructor

		// Callbacks
		// ----------------------------------------------------------------------------
		static void FrameBufferSizeCallback(GLFWwindow* window, int width,  int height);
		static void KeyboardKeyCallback    (GLFWwindow* window, int key,    int code,   int action, int mods);
		static void MouseButtonCallback    (GLFWwindow* window, int button, int action, int mods);
		static void CursorPositionCallback (GLFWwindow* window, double xpos, double ypos);
	};

} }