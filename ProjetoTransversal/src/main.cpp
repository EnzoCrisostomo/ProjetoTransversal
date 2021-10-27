#include <glad/glad.h>

#include "Options/Options.h"
#include "Application.h"

int main()
{
	Application app(Options::windowName, (int)Options::windowWidth, (int)Options::windowHeight);
	app.setup();
	//Loop principal do programa
	app.runLoop();
	return 0;
}