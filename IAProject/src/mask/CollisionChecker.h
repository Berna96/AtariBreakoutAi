/*
 * CollisionChecker.h
 *
 *  Created on: 4 ott 2019
 *      Author: Berna
 */

#ifndef MASK_COLLISIONCHECKER_H_
#define MASK_COLLISIONCHECKER_H_
#include "../GameObject.h"
#include "RectCollisionMask.h"
#include "CircleCollisionMask.h"

namespace mask {

class CollisionChecker {
public:
	static bool checkCollision(const GameObject*, const GameObject*);
};

} /* namespace mask */

#endif /* MASK_COLLISIONCHECKER_H_ */
