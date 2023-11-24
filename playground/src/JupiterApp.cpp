// C++ system includes
#include <cstdint>

// Own includes
#include <jupiter/Jupiter.h>

class JupiterApp : public jupiter::Application {
public:
    JupiterApp() {}

    ~JupiterApp() {}
};

jupiter::Application* jupiter::createApplication() { return new JupiterApp(); }
