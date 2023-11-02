#pragma once

<<<<<<< HEAD
// Own includes
#include "Logger.h"

=======
>>>>>>> 0c230a1b2cdf266a776bc4a48c2468d7a40f9343
#ifdef JUPITER_PLATFORM_WINDOWS

extern jupiter::Application* jupiter::createApplication();

int main(int* argc, char** argv) {
<<<<<<< HEAD
    jupiter::Logger::init();
    LOG_INFO("Logger initialized");

    jupiter::Application* game = jupiter::createApplication();
    game->run();
    delete game;

=======
    jupiter::Application* game = jupiter::createApplication();
    game->run();
    delete game;
>>>>>>> 0c230a1b2cdf266a776bc4a48c2468d7a40f9343
    return 0;
}

#endif
