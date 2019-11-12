/*
 * Ball.cpp
 *
 *  Created on: 28 set 2019
 *      Author: Berna
 */

#include "Ball.h"
#include "game.h"
#include "Board.h"
#include "Brick.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Ball::Ball() : ball(nullptr), ray(10.f), pos(Vector2u(540 - 10, 680-20-10 -1)){
	 std::srand(time(0));
	 int sign = rand() % 2;
	 if (sign == 0) sign = -1;
	 speed = Vector2f(sign * 70, -100);
	 ball = new CircleShape(ray);
	 ball->setPointCount(10);
	 ball->setFillColor(Color::White);
	 ball->setPosition(540 - 10, 680-20-10 -1);	//680-10-10
	 mask = new mask::CircleCollisionMask(ball);
	 tag = GameObject::BALL;
}

void Ball::update(sf::Keyboard::Key& key){
	double dt = GameUtils::deltaFrame;
	Vector2f ds = Vector2f(speed.x * dt, speed.y * dt);
	if ((ball->getPosition().x + ds.x) < 0 || (ball->getPosition().x + 2 * ray + ds.x) > GameUtils::RESOLUTION.x){
		ds = Vector2f(0,0);
		speed.x = -speed.x;
	}else if ((ball->getPosition().y - 2 * ray+ ds.y) < 0){
		ds = Vector2f(0,0);
		speed.y = -speed.y;
	}else if ((ball->getPosition().y + ds.y) > GameUtils::RESOLUTION.y){
		GameUtils::CURRENT_STATE = GameUtils::GAME_OVER;
	}
	ball->setPosition(ball->getPosition() + ds);
	circleCenter = ball->getPosition() + Vector2f(ball->getRadius(), ball->getRadius());
}

void Ball::onCollisionEnter(const GameObject* object){
	/*Border Collision*/
	if (object->tag == GameObject::BRICK){
		Brick* brick = (Brick*) object;
		mask::RectCollisionMask* mask = (mask::RectCollisionMask*) brick->mask;
		if (mask->side == mask::RectCollisionMask::LEFT ||
				mask->side == mask::RectCollisionMask::RIGHT){
			speed = Vector2f(-speed.x, speed.y);
		}else if (mask->side == mask::RectCollisionMask::UP ||
				mask->side == mask::RectCollisionMask::DOWN){
			speed = Vector2f(speed.x, -speed.y);
		}else if (mask->side == mask::RectCollisionMask::POINT){
			speed = -speed;
		}
	}else if (object->tag == GameObject::BOARD){
		Board* board = (Board*) object;
		mask::RectCollisionMask* mask = (mask::RectCollisionMask*) board->mask;
		if (mask->side == mask::RectCollisionMask::LEFT ||
				mask->side == mask::RectCollisionMask::RIGHT){
			speed = Vector2f(-speed.x, speed.y);
		}else if (mask->side == mask::RectCollisionMask::UP ||
				mask->side == mask::RectCollisionMask::DOWN){
			speed = Vector2f(speed.x, -speed.y);
		}else if (mask->side == mask::RectCollisionMask::POINT){
			speed = -speed;
		}
	}
}

void Ball::draw(RenderWindow& window){
	window.draw(*ball);
}

Ball::~Ball() {
	if (ball!=nullptr)	delete ball;
}

