#pragma once

// Own includes
#include "Logger.h"

#ifdef JUPITER_PLATFORM_WINDOWS

extern jupiter::Application* jupiter::createApplication();

int main(int* argc, char** argv) {
    int info = 5;
    LOG_INFO("message = {}", info);

    jupiter::Application* game = jupiter::createApplication();
    game->run();
    delete game;

    return 0;
}

#endif
