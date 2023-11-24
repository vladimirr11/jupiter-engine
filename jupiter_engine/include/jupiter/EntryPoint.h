#pragma once

// Own includes
#include "Logger.h"
#include "Application.h"

#ifdef JUPITER_PLATFORM_WINDOWS

extern jupiter::Application* jupiter::createApplication();

int main(int argc, char** argv) {
	LOG_INFO("Engine started");

	jupiter::Application* game = jupiter::createApplication();
	game->run();
	delete game;

	return 0;
}

#endif
