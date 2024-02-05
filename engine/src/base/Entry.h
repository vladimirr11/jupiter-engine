#pragma once

// Own includes
#include "base/Application.h"

#if defined(JUPITER_PLATFORM_WINDOWS) || defined(JUPITER_PLATFORM_LINUX)

extern jupiter::Application* jupiter::createApplication();

int32 main(int32 argc, char** argv) {
    JLOG_INFO("Engine started");

    jupiter::Application* app = jupiter::createApplication();
    app->run();
    delete app;

    return 0;
}

#endif
