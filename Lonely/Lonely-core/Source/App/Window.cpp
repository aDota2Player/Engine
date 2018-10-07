#include "Window.h"

#include "Debug/ImGui/imgui.h"
#include "Debug/ImGui/imgui_impl_glfw_gl3.h"

#include <iostream>

namespace lonely { namespace app {

	Window::Window()
		: m_Width(LONELY_DEFAULT_WINDOW_WIDTH), m_Height(LONELY_DEFAULT_WINDOW_HEIGHT), m_Title(LONELY_DEFAULT_WINDOW_TITLE),
		  b_FullScreen()
	{
		if (!Initialize(0))
			std::cout << "[ ERROR ]: Failed to initialize game" << std::endl;
	}

	Window::Window(unsigned int width, unsigned int height, char* title, unsigned int glfwSamples /* = 0 */, bool fullScreen /* = false */)
		: m_Width(width), m_Height(height), m_Title(title),
		  b_FullScreen(fullScreen)
	{
		if (!Initialize(glfwSamples))
			std::cout << "[ ERROR ]: Failed to initialize game" << std::endl;
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	bool Window::Initialize(unsigned int samples)
	{
		if (!glfwInit()) 
		{
			std::cout << "[ ERROR ]: Failed to initialize glfw" << std::endl;
			return false;
		}
		
		glfwWindowHint(GLFW_SAMPLES, samples);

		if (b_FullScreen)
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL);
		else
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetFramebufferSizeCallback(m_Window, FrameBufferSizeCallback);
		glfwSetKeyCallback(m_Window, KeyboardKeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, CursorPositionCallback);

		if (m_Window == NULL)
		{
			std::cout << "[ ERROR ]: Failed to create glfw window" << std::endl;
			return false;
		}

		if (glewInit() != GLEW_OK)
		{
			std::cout << "[ ERROR ]: Failed to initialize glew" << std::endl;
			return false;
		}

		std::cout << "[ OpenGL Version ]: " << glGetString(GL_VERSION) << std::endl;
		return true;
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::ClearColor(float r, float g, float b)
	{
		glClearColor(r, g, b, 1.0f);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::InitializeImGui(bool install_callbacks /* = false */)
	{
		ImGui_ImplGlfwGL3_Init(m_Window, install_callbacks);
	}

	// Callbacks
	// ----------------------------------------------------------------------------
	void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* gameWindow = (Window*)glfwGetWindowUserPointer(window);
		gameWindow->m_Width = width;
		gameWindow->m_Height = height;

		if (gameWindow->m_Framebuffer)
			gameWindow->m_Framebuffer->SetSize(width, height);

		glViewport(0, 0, width, height);
	}

	void Window::KeyboardKeyCallback(GLFWwindow* window, int key, int code, int action, int mods)
	{
		Window* gameWindow = (Window*)glfwGetWindowUserPointer(window);
		
		if (gameWindow->m_Controller)
		{
			gameWindow->m_Controller->m_Keys[key] = (KeyboardKey)action;
			gameWindow->m_Controller->m_LastKey = key;
		}
	}

	void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* gameWindow = (Window*)glfwGetWindowUserPointer(window);
		
		if (gameWindow->m_Controller) 
		{
			gameWindow->m_Controller->m_Buttons[button] = (MouseButton)action;
			gameWindow->m_Controller->m_LastButton = button;
		}
	}

	void Window::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* gameWindow = (Window*)glfwGetWindowUserPointer(window);
		
		if (gameWindow->m_Controller)
		{
			gameWindow->m_Controller->m_MouseX = xpos;
			gameWindow->m_Controller->m_MouseY = ypos;
		}
	}

} }