//============================================================================
// Name        : IAProject.cpp
// Author      : ilBerna
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "game.h"
#include "mask/CollisionChecker.h"
#include "Brick.h"
#include "Board.h"
#include "Ball.h"
#include "menu/Menu.h"
#include "GameOver.h"
#include <map>
#include <list>
#include <string>
using namespace sf;
using namespace std;

/*get undefine reference to error*/
sf::Vector2u GameUtils::RESOLUTION = sf::Vector2u(1080, 680);
unsigned int GameUtils::GAMEPOINTS = 0;
int GameUtils::CURRENT_STATE = gamestates::MENU;
double GameUtils::deltaFrame = 1.0/60.0;
string GameUtils::BRICK = "NONE";
unsigned int GameUtils::count_brick = 0;

int main()
{

	//Initialization
	sf::RenderWindow window(VideoMode(GameUtils::RESOLUTION.x, GameUtils::RESOLUTION.y), "Atari Breakout");
    window.setPosition(Vector2i(10, 0)); 	//distanza 10, 5 rispetto al desktop
    window.setVerticalSyncEnabled(true);	//attivo il vsync

    //Time Counting
    Clock clock;

    //Declaration
    menu::Menu* menu = nullptr;
    Board* board = nullptr;
    Ball* ball = nullptr;
    GameOver* gameOver = nullptr;
    Keyboard::Key key = Keyboard::Key::Unknown;
    bool list_brick = false;
    bool ai = false;
    int eps = 8;
    int currentState = ai::Mdp::C;

    map<string, GameObject*> objects;
    sf::Color brickColors[5] = {sf::Color::Red,
    				sf::Color::Magenta, sf::Color::Yellow,
    				sf::Color::Green, sf::Color::Blue};

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed){
				key = event.key.code;
			}else if (event.type == Event::KeyReleased){
				key = Keyboard::Key::Unknown;
			}

        }
        //Clear
        //Automa a stati : MENU -> AI o PLAYER
        window.clear(sf::Color::Black);

        /*MENU*/
        if (GameUtils::CURRENT_STATE== GameUtils::gamestates::MENU){
        	//Menu game logic
        	if (menu == nullptr){
        		menu = new menu::Menu();	//dovrebbe essere singleton
        		objects.insert(pair<string, GameObject*>("MENU", menu));
        	}

        }else if (GameUtils::CURRENT_STATE == GameUtils::GAME_INIT_CPU ||
        		GameUtils::CURRENT_STATE == GameUtils::GAME_INIT_PLAYER){
        	//delete menu
        	objects.erase("MENU");
        	delete menu;
        	menu = nullptr;

			board = new Board();
	        objects.insert(pair<string, GameObject*>("BOARD", board));

	        for (int i=0; i< 50; i++){
				int x = i % 10;
				int y = int(i/10);
				Brick* brick = new Brick(x, y);
				brick->setProperties(brickColors[4 - y], 5);
				string brick_str = "BRICK";
				objects.insert(pair<string, GameObject*>(brick_str.append(std::to_string(i)), brick));
			}
	        if (GameUtils::CURRENT_STATE == GameUtils::GAME_INIT_CPU)	GameUtils::CURRENT_STATE = GameUtils::GAME_PRE_CPU;
	        if (GameUtils::CURRENT_STATE == GameUtils::GAME_INIT_PLAYER)	GameUtils::CURRENT_STATE = GameUtils::GAME_PLAYER;
        }else if (GameUtils::CURRENT_STATE == GameUtils::gamestates::GAME_PLAYER){
        	//Player logic
        	if (ball==nullptr){
        		ball = new Ball();
        		objects.insert(pair<string, GameObject*>("BALL", ball));
        	}
        	if (GameUtils::BRICK != "NONE"){
        		objects.erase(GameUtils::BRICK);
        		GameUtils::count_brick++;
        		GameUtils::BRICK = "NONE";
        	}
        	if (GameUtils::count_brick == 50){
        		GameUtils::CURRENT_STATE = GameUtils::gamestates::GAME_OVER;
        	}

        }else if (GameUtils::CURRENT_STATE == GameUtils::gamestates::GAME_PRE_CPU){
        	board->setAI();
        	if (board->learningPhase())	GameUtils::CURRENT_STATE = GameUtils::gamestates::GAME_CPU;
        }else if (GameUtils::CURRENT_STATE == GameUtils::gamestates::GAME_CPU){
        	if (ball==nullptr){
				ball = new Ball();
				objects.insert(pair<string, GameObject*>("BALL", ball));
			}
        	float size_2 = 0.5 * (GameUtils::RESOLUTION.x/10) - eps;
        	if (((board->rectCenter.x - size_2) <= ball->circleCenter.x) && (ball->circleCenter.x <= (board->rectCenter.x + size_2))){
        		currentState = ai::Mdp::C;
        	}else if ((board->rectCenter.x - size_2) > ball->circleCenter.x){
        		//LEFT
        		if (ball->circleCenter.y < 0){
        			currentState = ai::Mdp::UL;
        		}else{
        			currentState = ai::Mdp::DL;
        		}
        	}else{
        		//RIGHT
        		if (ball->circleCenter.y < 0){
        			currentState = ai::Mdp::UR;
        		}else{
					currentState = ai::Mdp::DR;
				}
        	}
        	board->setCurrentState(currentState);
        	//cout << "Current State: " << currentState << endl;
        	if (GameUtils::BRICK != "NONE"){
				objects.erase(GameUtils::BRICK);
				GameUtils::count_brick++;
				GameUtils::BRICK = "NONE";
			}
			if (GameUtils::count_brick == 50){
				GameUtils::CURRENT_STATE = GameUtils::gamestates::GAME_OVER;
			}
        }else if (GameUtils::CURRENT_STATE == GameUtils::gamestates::GAME_OVER){
        	if (ball != nullptr){
				objects.erase("BALL");
				delete ball;
				ball = nullptr;
			}
        	if (board != nullptr){
				objects.erase("BOARD");
				ai = board->getAI();
				delete board;
				board = nullptr;
			}

        	if (ball != nullptr){
				objects.erase("MENU");
				delete menu;
				menu = nullptr;
			}
        	if (!list_brick){
				list_brick = true;
				for (int i=0; i< 50; i++){
					string brick_str = "BRICK";
					objects.erase(brick_str.append(std::to_string(i)));
				}
			}
        	if (gameOver == nullptr){
        		gameOver = new GameOver(ai);
        		objects.insert(pair<string, GameObject*>("GAME_OVER", gameOver));
			}
        }

        //Game Logic
        map<string, GameObject*>::iterator i, j, l;

        for (i = objects.begin(); i!=objects.end(); i++){
        	l = i;
        	for (j = ++l; j!=objects.end(); j++){
        		if (mask::CollisionChecker::checkCollision(i->second, j->second)){
        			i->second->onCollisionEnter(j->second);
        			j->second->onCollisionEnter(i->second);
        		}
        	}
        	i->second->update(key);
        	i->second->draw(window);
        }

        //fps count
		double currentTime = clock.restart().asMilliseconds();
		GameUtils::deltaFrame = currentTime / 1000;
		window.display();

    }

    return 0;
}
