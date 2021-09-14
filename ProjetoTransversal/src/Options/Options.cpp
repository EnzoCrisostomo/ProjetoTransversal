#include "Options.h"

//Window
	  float	 Options::windowWidth = 1280.0f; //Largura da janela
	  float	 Options::windowHeight = 720.0f; //Altura da janela
const char*  Options::windowName = "******"; //Label da janela

//Player
const float  Options::fov = 75.0f; //Fov do jogador
const double Options::mouseSensibility = 0.2;
const float  Options::playerSpeed = 10.0f;
const int    Options::playerGamemode = 1; //0 = (TODO)survival //1 = creative

//World
const int	 Options::viewDistance = 8; //Distância em relação ao player que chunks serão renderizadas
const int	 Options::loadDistance = Options::viewDistance + 4; //Distância em relação ao player que chunks serão carregadas

bool Options::teste = false;