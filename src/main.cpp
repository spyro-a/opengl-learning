#include <cstdlib>

#include <engine/engine.hpp>

#define GL_SILENCE_DEPRECATION

int main() {
    // default constructor gives a window size of 800x600
    engine_t engine;
    // engine.set_wireframe_mode(false);
    
    engine.initialize();
    engine.run();
    engine.destroy();

    return EXIT_SUCCESS;
}