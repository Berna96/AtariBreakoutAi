/*
 * CollisionMask.h
 *
 *  Created on: 4 ott 2019
 *      Author: Berna
 */

#ifndef MASK_COLLISIONMASK_H_
#define MASK_COLLISIONMASK_H_

#include <SFML/Graphics.hpp>

namespace mask {

class CircleCollisionMask;
class RectCollisionMask;

enum type {CIRCLE, RECTANGLE, NONE};

class CollisionMask {
public:
	sf::Vector2f hitPoint;
	virtual bool collideWith(CollisionMask*) = 0;
	virtual bool collideWithCircle(CircleCollisionMask*) = 0;
	virtual bool collideWithRectangle(RectCollisionMask*) = 0;
	virtual ~CollisionMask(){};
};

} /* namespace mask */

#endif /* MASK_COLLISIONMASK_H_ */
