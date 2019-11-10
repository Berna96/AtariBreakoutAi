/*
 * RectCollisionMask.cpp
 *
 *  Created on: 4 ott 2019
 *      Author: Berna
 */

#include "RectCollisionMask.h"
#include "CircleCollisionMask.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace mask {
//class CircleCollisionMask;


RectCollisionMask::RectCollisionMask(sf::RectangleShape* rect) : side(NONE), rect(rect){}

bool RectCollisionMask::collideWith(CollisionMask* mask){
	return mask->collideWithRectangle(this);
}

/*no implementation*/
bool RectCollisionMask::collideWithRectangle(RectCollisionMask* mask){
	return false;
}

bool RectCollisionMask::collideWithCircle(CircleCollisionMask* circleMask){
	return circleMask->collideWithRectangle(this);
}

RectCollisionMask::~RectCollisionMask() {
}

} /* namespace mask */
