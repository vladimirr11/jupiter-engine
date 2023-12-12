#pragma once

// Own includes
#include "Application.h"

#ifdef JUPITER_PLATFORM_WINDOWS

extern jupiter::Application* jupiter::createApplication();

int32 main(int32 argc, char** argv) {
    JLOG_INFO("Engine started");

    jupiter::Application* app = jupiter::createApplication();
    app->run();
    delete app;

    return 0;
}

#endif
