#include "Engine/Window.h"

int main(void)
{

    Engine::Window window(640, 480, "Cube Game");
    window.Render();

    return 0;
}