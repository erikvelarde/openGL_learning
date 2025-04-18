#include "Application.h"
#include <iostream>

int main()
{
	if (true) std::cout << "hello world" << std::endl;

	try {
		Application app(800, 600, "Moving Circle");
		app.run();
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
