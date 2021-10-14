#include "Options.h"

//Window
	  double Options::windowWidth = 1280.0; //Largura da janela
	  double Options::windowHeight = 720.0; //Altura da janela
const char*  Options::windowName = "Minecraft!!!"; //Label da janela

//Player
const double Options::fov = 75.0; //Fov do jogador
const double Options::mouseSensibility = 0.2;
const double Options::playerSpeed = 0.5;
const int    Options::playerGamemode = 1; //0 = (TODO)survival //1 = creative

//World
const int	 Options::viewDistance = 14; //Distância em relação ao player que chunks serão renderizadas
const int	 Options::loadDistance = Options::viewDistance + 4; //Distância em relação ao player que chunks serão carregadas
const int	 Options::waterLevel = 64;

bool Options::teste = false;