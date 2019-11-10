/*
 * Board.h
 *
 *  Created on: 15 mag 2019
 *      Author: Berna
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "game.h"
#include "ai/Mdp.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class Board : public GameObject{
public:
	sf::Vector2f rectCenter;
	Board();
	virtual void setPlayer();
	virtual void setCurrentState(int);
	bool learningPhase();
	virtual void setAI();
	virtual bool getAI();
	virtual void update(sf::Keyboard::Key&);
	void onCollisionEnter(const GameObject*);
	void draw(sf::RenderWindow&);
	virtual ~Board();
private:
	sf::RectangleShape* rect;
	bool ai, first;
	float eps;
	float acc;
	float speedx;
	float speedMax;
	int command;
	ai::Mdp mdp;
	int currentState;
	float f;
};

#endif /* BOARD_H_ */
