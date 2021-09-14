#include <glad/glad.h>
#include <iostream>

#include "Options/Options.h"
#include "Application.h"

int main()
{
    Application app(Options::windowName, (int)Options::windowWidth, (int)Options::windowHeight);
    //Loop principal do programa
    app.runLoop();
    return 0;
}