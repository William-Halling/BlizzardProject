#include <iostream>

#include "Application.h"

constexpr uint32_t MAX_ENTITES = 1000;


int main()
{
	try
	{
		std::cout << "Bootstrapping Engine Lifecycle Context...\n";
		Engine::Core::Application app;

		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Engine crashed due to unhandled fatal exception: " << e.what() << "\n";
		return -1;
	}

	std::cout << "Engine Lifecycle shutdown gracefully.\n";

	return 0;
}