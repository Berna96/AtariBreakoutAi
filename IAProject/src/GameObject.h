/*
 * GameObject.h
 *
 *  Created on: 29 set 2019
 *      Author: Berna
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "mask/CollisionMask.h"
#include "mask/CircleCollisionMask.h"
#include "mask/RectCollisionMask.h"

class GameObject {
public:
	/*remove*/
	enum tag {NONE, BOARD, BORDER, BRICK, WALL, BALL, MENU};	//TODO:remove
	int tag;
	/**/
	GameObject() : mask(nullptr){};
	mask::CollisionMask* mask;
	virtual void update(sf::Keyboard::Key&) = 0;
	virtual void onCollisionEnter(const GameObject*){};
	virtual void draw(sf::RenderWindow&) = 0;
	~GameObject(){ if (mask==nullptr)	delete mask;}
};

#endif /* GAMEOBJECT_H_ */
