#include "Window.h"
#include <iostream>


namespace Engine::Core
{
	Window::Window(const WindowConfiguration& config)
	{
		if (!glfwInit())
		{
			std::cerr << "Fatal: GLFW initialization failed.\n";
			std::exit(-1);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.glVersionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.glVersionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_WindowHandle = glfwCreateWindow(config.width, config.height, config.title.data(), nullptr, nullptr);
		
		if (!m_WindowHandle)
		{
			std::cerr << "Fatal: Failed to create GLFW window context.\n";
			glfwTerminate();
			std::exit(-1);
		}

		glfwMakeContextCurrent(m_WindowHandle);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Fatal: Failed to map GLAD function pointers.\n";
			std::exit(-1);
		}
	}


	Window::~Window() noexcept
	{
		if (m_WindowHandle)
		{
			glfwDestroyWindow(m_WindowHandle);
		}

		glfwTerminate();
	}

	bool Window::ShouldClose() const noexcept
	{
		return glfwWindowShouldClose(m_WindowHandle);
	}

	void Window::PollEvents() const noexcept
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers() const noexcept
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}