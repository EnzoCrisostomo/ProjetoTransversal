#pragma once
//Struct que contém todas opções do programa

struct Options
{
	//Window
	static			 float	windowWidth;
	static			 float	windowHeight;
	static const	 char*  windowName;

	//Player
	static const	 float  fov;
	static const	 double mouseSensibility;
	static const	 float  playerSpeed;
	static const	 int    playerGamemode;

	//Chunk
	static constexpr int	chunkColumnHeigth = 8;
	static constexpr int	chunkSize = 16;
	static constexpr int	chunkArea = chunkSize * chunkSize;
	static constexpr int	chunkVolume = chunkSize * chunkArea;

	//World
	static const     int	viewDistance;
	static const     int	loadDistance;

	static bool teste;

	Options() = delete;
};