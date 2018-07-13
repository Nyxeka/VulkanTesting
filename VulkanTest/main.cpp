#include "stdafx.h"

#include "VulkanApp.h"

#include <cstdlib>
#include <stdexcept>
#include <iostream>


int main() {
	VulkanApp app;

	try {
		app.run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}