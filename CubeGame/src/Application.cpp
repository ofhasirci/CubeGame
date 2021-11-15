#include "Engine/Window.h"
#include "Game/Scene.h"

int main(void)
{
    Engine::Window window(960, 540, "Cube Game");
    window.Render();

    return 0;
}