#pragma once
#include <string>
//Struct que contém todas opções do programa

struct Options
{
	//Window
	static			 double	windowWidth;
	static			 double	windowHeight;
	static const	 char*  windowName;

	//Player
	static const	 double fov;
	static const	 double mouseSensibility;
	static const	 double playerSpeed;
	static const	 int    playerGamemode;

	//Chunk
	static constexpr int	chunkColumnHeigth = 8;
	static constexpr int	chunkSize = 16;
	static constexpr int	chunkArea = chunkSize * chunkSize;
	static constexpr int	chunkVolume = chunkSize * chunkArea;

	//World
	static const     int	viewDistance;
	static const     int	loadDistance;
	static const     int	waterLevel;

	//FileSys
	static const	 std::string dataPath;
	static const	 std::string savePath;
	static			 std::string worldRegionsPath;
	static constexpr bool	saveEnabled = true;
	static constexpr int	regionSize = 8;

	static bool teste;

	Options() = delete;
};