#pragma once
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

	static bool teste;

	Options() = delete;
};