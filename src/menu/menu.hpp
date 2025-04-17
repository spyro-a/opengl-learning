#pragma once

#include <string>

class engine_t;

class menu_t {
private:
    engine_t* state;

    std::string title;
    float width, height;

    bool showing;

public:
    menu_t();

    void initialize(engine_t* e);
    void render();
    void destroy();

    inline void toggle() { showing = !showing; }

    inline bool is_showing() const { return showing; }
};