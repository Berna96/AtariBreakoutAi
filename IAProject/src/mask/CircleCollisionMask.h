/*
 * CircleCollisionMask.h
 *
 *  Created on: 4 ott 2019
 *      Author: Berna
 */

#ifndef MASK_CIRCLECOLLISIONMASK_H_
#define MASK_CIRCLECOLLISIONMASK_H_

#include "CollisionMask.h"
#include <SFML/Graphics.hpp>

namespace mask {
class RectCollisionMask;

class CircleCollisionMask : public CollisionMask{
public:
	sf::CircleShape* circle;
	CircleCollisionMask(sf::CircleShape*);
	bool collideWith(CollisionMask*);
	bool collideWithCircle(CircleCollisionMask*);
	bool collideWithRectangle(RectCollisionMask*);
	virtual ~CircleCollisionMask();
};

} /* namespace mask */

#endif /* MASK_CIRCLECOLLISIONMASK_H_ */
