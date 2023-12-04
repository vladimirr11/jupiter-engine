#pragma once

// Own includes
#include "Logger.h"
#include "Application.h"

#ifdef JUPITER_PLATFORM_WINDOWS

extern jupiter::Application* jupiter::createApplication();

int main(int argc, char** argv) {
    JLOG_INFO("Engine started");

    jupiter::Application* app = jupiter::createApplication();
    app->run();
    delete app;

    return 0;
}

#endif
