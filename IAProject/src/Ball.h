/*
 * Ball.h
 *
 *  Created on: 28 set 2019
 *      Author: Berna
 */

#ifndef BALL_H_
#define BALL_H_

#include <SFML/Graphics.hpp>
#include "GameObject.h"
using namespace sf;

class Ball : public GameObject{
public:
	Vector2f circleCenter;
	sf::Vector2f speed;
	Ball();
	void update(sf::Keyboard::Key&);
	void onCollisionEnter(const GameObject*);
	void draw(RenderWindow&);
	virtual ~Ball();
private:
	CircleShape* ball;
	float ray;
	sf::Vector2u pos;
};

#endif /* BALL_H_ */
