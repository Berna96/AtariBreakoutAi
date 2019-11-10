#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

class GameUtils{
public:
	enum gamestates {MENU, GAME_INIT_PLAYER, GAME_INIT_CPU, GAME_PLAYER, GAME_PRE_CPU, GAME_CPU, AI_WINS, GAME_OVER};
	enum command {LEFT, STOP, RIGHT, NONE};
	static sf::Vector2u RESOLUTION;
	static unsigned int GAMEPOINTS;
	static int CURRENT_STATE;
	static double deltaFrame;
	//Brick
	static std::string BRICK;
	static unsigned int count_brick;
};

#endif
