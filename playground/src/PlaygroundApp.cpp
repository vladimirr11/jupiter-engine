// C++ system includes
#include <cstdint>

// Own includes
#include <Jupiter.h>

class PlaygroundApp : public jupiter::Application {
public:
    PlaygroundApp() {}

    ~PlaygroundApp() {}
};

jupiter::Application* jupiter::createApplication() { return new PlaygroundApp(); }
