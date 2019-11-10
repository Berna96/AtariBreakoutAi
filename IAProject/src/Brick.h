/*
 * Brick.h
 *
 *  Created on: 12 mag 2019
 *      Author: Berna
 */

#ifndef BRICK_H_
#define BRICK_H_

#include "SFML/Graphics.hpp"
#include "GameObject.h"

class Brick : public GameObject{
public:
	Brick(int, int);
	//Brick(const Brick&);
	virtual void setProperties(sf::Color , int, sf::Color = sf::Color::White);
	virtual void onCollisionEnter(const GameObject*);
	virtual void update(sf::Keyboard::Key&) {};
	virtual void draw(sf::RenderWindow&);
	virtual ~Brick();

private:
	sf::RectangleShape *rect;
	int row;
	int index; 	//a partire da destra!!!
	int life;
	unsigned int reward;
};
#endif /* BRICK_H_ */

