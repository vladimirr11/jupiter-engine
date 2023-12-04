// C++ system includes
#include <cstdint>

// Own includes
#include <Jupiter.h>

class JupiterApp : public jupiter::Application {
public:
    JupiterApp() {}

    ~JupiterApp() {}
};

jupiter::Application* jupiter::createApplication() { return new JupiterApp(); }
