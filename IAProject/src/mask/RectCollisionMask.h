/*
 * RectCollisionMask.h
 *
 *  Created on: 4 ott 2019
 *      Author: Berna
 */

#ifndef MASK_RECTCOLLISIONMASK_H_
#define MASK_RECTCOLLISIONMASK_H_

#include "CollisionMask.h"
#include <SFML/Graphics.hpp>

namespace mask {
class CircleCollisionMask;

class RectCollisionMask: public CollisionMask {
public:
	enum sides {NONE, LEFT, RIGHT, UP, DOWN, POINT};
	int side;
	sf::RectangleShape* rect;
	RectCollisionMask(sf::RectangleShape*);
	bool collideWith(CollisionMask*);
	bool collideWithCircle(CircleCollisionMask*);
	bool collideWithRectangle(RectCollisionMask*);
	virtual ~RectCollisionMask();
};

} /* namespace mask */

#endif /* MASK_RECTCOLLISIONMASK_H_ */
