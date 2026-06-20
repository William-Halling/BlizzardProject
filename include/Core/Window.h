#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string_view>


namespace Engine::Core
{
	struct WindowConfiguration
	{
		int width  { 1200 };
		int height { 720 };
		std::string_view title{"C++ Systems Engine"};
		int glVersionMajor{ 4 };
		int glVersionMinor{ 4 };
	};


	class Window
	{
		private:
			GLFWwindow* m_WindowHandle{ nullptr };

		public:
			explicit Window(const WindowConfiguration & config);
			

			~Window() noexcept;


			Window(const Window&) = delete;
			

			Window& operator=(const Window&) = delete;


			[[nodiscard]] bool ShouldClose() const noexcept;


			void PollEvents() const noexcept;
			
			
			void SwapBuffers() const noexcept;
			

			[[nodiscard]] GLFWwindow* GetNativeHandle() const noexcept { return m_WindowHandle; }
	};
}

