/*
 * CollisionChecker.cpp
 *
 *  Created on: 4 ott 2019
 *      Author: Berna
 */

#include "CollisionChecker.h"
#include <iostream>
using namespace std;

namespace mask {

bool CollisionChecker::checkCollision(const GameObject* obj1, const GameObject* obj2){
	if (obj1->mask == nullptr || obj2->mask == nullptr)	return false;
	return obj1->mask->collideWith(obj2->mask);
}

} /* namespace mask */
