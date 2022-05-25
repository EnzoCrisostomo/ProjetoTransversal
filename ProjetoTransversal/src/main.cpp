#include <glad/glad.h>

#include "Options/Options.h"
#include "Application.h"

//enable optimus NVIDIA gpu
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
}

//enable laptop AMD gpu
extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main()
{
	Application app(Options::windowName, (int)Options::windowWidth, (int)Options::windowHeight);
	app.setup();
	//Loop principal do programa
	app.runLoop();
	return 0;
}