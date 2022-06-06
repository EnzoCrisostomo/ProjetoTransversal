#include "Options.h"

//Window
	  double Options::windowWidth = 1280.0; //Largura da janela
	  double Options::windowHeight = 720.0; //Altura da janela
const char*  Options::windowName = "Minecraft!!!"; //Label da janela

//Player
const double Options::fov = 75.0; //Fov do jogador
const double Options::mouseSensibility = 0.2;
const double Options::playerSpeed = 0.5;
const int    Options::playerGamemode = 2; //0 = survival //1 = creative //2= spectator

//World
const int	 Options::viewDistance = 16; //Distância em relação ao player que chunks serão renderizadas
const int	 Options::loadDistance = Options::viewDistance + 4; //Distância em relação ao player que chunks serão carregadas
const int	 Options::waterLevel = 64;

//FileSys
const std::string Options::dataPath = "./data/"; //Pasta de saves
const std::string Options::savePath = Options::dataPath + "saves/"; //Pasta de saves
	  std::string Options::worldRegionsPath = Options::dataPath + "dump/"; //Pasta de saves

bool Options::teste = true;