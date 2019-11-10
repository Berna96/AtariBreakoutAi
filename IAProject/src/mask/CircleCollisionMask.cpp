/*
 * CircleCollisionMask.cpp
 *
 *  Created on: 4 ott 2019
 *      Author: Berna
 */

#include "CircleCollisionMask.h"
#include "RectCollisionMask.h"
//#include "CollisionMask.h"	/**/
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

namespace mask {

CircleCollisionMask::CircleCollisionMask(CircleShape* circle)
		: circle(circle){}

bool CircleCollisionMask::collideWith(CollisionMask* mask){
	return mask->collideWithCircle(this);
}

//Circle-Circle Collision : non avviene mai
bool CircleCollisionMask::collideWithCircle(CircleCollisionMask* circleMask){
	Vector2f diff = this->circle->getOrigin() - circleMask->circle->getOrigin();
	double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
	return magnitude <= (this->circle->getRadius() + circleMask->circle->getRadius());
}

//Rect-Circle Collision
bool CircleCollisionMask::collideWithRectangle(RectCollisionMask* rectMask){
	//TODO: implementare rect-circle
	Vector2f circleCenter = this->circle->getPosition() + Vector2f(this->circle->getRadius(), this->circle->getRadius());
	Vector2f circleUp = circleCenter + Vector2f(0, - this->circle->getRadius());
	Vector2f circleDown = circleCenter + (Vector2f(0, this->circle->getRadius()) );
	Vector2f circleLeft = circleCenter + (Vector2f( - this->circle->getRadius(), 0));
	Vector2f circleRight = circleCenter + (Vector2f( this->circle->getRadius(), 0));

	Vector2f rectCenter = rectMask->rect->getPosition() +
			Vector2f(rectMask->rect->getSize().x/2, rectMask->rect->getSize().y/2);
	Vector2f point0 = rectMask->rect->getTransform().transformPoint(rectMask->rect->getPoint(0));
	Vector2f point1 = rectMask->rect->getTransform().transformPoint(rectMask->rect->getPoint(1));
	Vector2f point2 = rectMask->rect->getTransform().transformPoint(rectMask->rect->getPoint(2));
	Vector2f point3 = rectMask->rect->getTransform().transformPoint(rectMask->rect->getPoint(3));

	/*Vector2f circleUp = this->circle->getTransform().transformPoint(Vector2f(0, - this->circle->getRadius()) );
	Vector2f circleDown = this->circle->getTransform().transformPoint(Vector2f(0, this->circle->getRadius()) );
	Vector2f circleLeft = this->circle->getTransform().transformPoint(Vector2f( - this->circle->getRadius(), 0));
	Vector2f circleRight = this->circle->getTransform().transformPoint(Vector2f( this->circle->getRadius(), 0));

	Vector2f point0 = rectMask->rect->getTransform().transformPoint(rectMask->rect->getPoint(0));
	Vector2f point1 = rectMask->rect->getTransform().transformPoint(rectMask->rect->getPoint(1));
	Vector2f point2 = rectMask->rect->getTransform().transformPoint(rectMask->rect->getPoint(2));
	Vector2f point3 = rectMask->rect->getTransform().transformPoint(rectMask->rect->getPoint(3));
	 */

	/*std::cout << "circleUp: " << circleUp.x << ", " << circleUp.y << std::endl;
	std::cout << "circleDown: " << circleDown.x << ", " << circleDown.y << std::endl;
	std::cout << "circleLeft: " << circleLeft.x << ", " << circleLeft.y << std::endl;
	std::cout << "circleRight: " << circleRight.x << ", " << circleRight.y << std::endl;

	std::cout << "Point0: " << point0.x << ", " << point0.y << std::endl;
	std::cout << "Point2: " << point2.x << ", " << point2.y << std::endl;
*/
	/*
	Vector2f pos = this->circle->getPosition();
	if (pos.x > rectMask->rect->getPosition().x){	//destra
		if (pos.y > point1.y && pos.y < point2.y){
			if (point1.x < circleLeft.x){
				//std::cout << "qua1" << std::endl;
				return false;
			}else{
				//std::cout << "qua2" << std::endl;
				rectMask->side = RectCollisionMask::LEFT;
				return true;
			}
		}
	}else{	//sinistra
		if (pos.y > point0.y && pos.y < point3.y){
			if (circleRight.x < point0.x ){
				//std::cout << "qua3" << std::endl;
				return false;
			}else{
				//std::cout << "qua4" << std::endl;

				rectMask->side = RectCollisionMask::RIGHT;
				return true;
			}
		}
	}

	if (pos.y < rectMask->rect->getPosition().y){	//sopra
		if (pos.x < point1.x && pos.x > point0.x){
			if (point1.y > circleDown.y){
				//std::cout << "qua5" << std::endl;
				return false;
			}else{
				//std::cout << "qua6" << std::endl;

				rectMask->side = RectCollisionMask::UP;
				return true;
			}
		}
	}else{	//sotto
		if (pos.x < point2.x && pos.x > point3.x){
			if (circleUp.y > point3.y ){
				//std::cout << "qua7" << std::endl;
				return false;
			}else{
				//std::cout << "qua8" << std::endl;
				rectMask->side = RectCollisionMask::DOWN;
				return true;
			}
		}
	}

	rectMask->side = RectCollisionMask::POINT;
	if (pos.x > point1.x){
		if (pos.y < point1.y){	//alto-destra
			Vector2f diff = point1 - pos;
			double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			return magnitude <= this->circle->getRadius();
		}else{		//basso destra
			Vector2f diff = point2 - pos;
			double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			return magnitude <= this->circle->getRadius();
		}
	}else if (pos.x < point0.x){
		if (pos.y < point0.y){	//alto-destra
			Vector2f diff = point0 - pos;
			double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			return magnitude <= this->circle->getRadius();
		}else{		//basso destra
			Vector2f diff = point3 - pos;
			double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			return magnitude <= this->circle->getRadius();
		}
	}
	*/
	//std::cout << "qua10" << std::endl;
	if (circleCenter.x > rectCenter.x){	//destra
		if (circleCenter.y > point1.y && circleCenter.y < point2.y){
			if (point1.x < circleLeft.x){
				//std::cout << "qua1" << std::endl;
				return false;
			}else{
				//std::cout << "qua2" << std::endl;
				rectMask->hitPoint = Vector2f(point1.x, circleCenter.y);
				rectMask->side = RectCollisionMask::LEFT;
				return true;
			}
		}
	}else{	//sinistra
		if (circleCenter.y > point0.y && circleCenter.y < point3.y){
			if (circleRight.x < point0.x ){
				//std::cout << "qua3" << std::endl;
				return false;
			}else{
				//std::cout << "qua4" << std::endl;
				rectMask->hitPoint = Vector2f(point0.x, circleCenter.y);
				rectMask->side = RectCollisionMask::RIGHT;
				return true;
			}
		}
	}

	if (circleCenter.y < rectCenter.y){	//sopra
		if (circleCenter.x < point1.x && circleCenter.x > point0.x){
			if (point1.y > circleDown.y){
				//std::cout << "qua5" << std::endl;
				return false;
			}else{
				//std::cout << "qua6" << std::endl;
				rectMask->hitPoint = Vector2f(circleCenter.x, point1.y);
				rectMask->side = RectCollisionMask::UP;
				return true;
			}
		}
	}else{	//sotto
		if (circleCenter.x < point2.x && circleCenter.x > point3.x){
			if (circleUp.y > point3.y ){
				//std::cout << "qua7" << std::endl;
				return false;
			}else{
				//std::cout << "qua8" << std::endl;
				rectMask->hitPoint = Vector2f(circleCenter.x, point3.y);
				rectMask->side = RectCollisionMask::DOWN;
				return true;
			}
		}
	}

	rectMask->side = RectCollisionMask::POINT;
	if (circleCenter.x > point1.x){
		if (circleCenter.y < point1.y){	//alto-destra
			Vector2f diff = point1 - circleCenter;
			double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			return magnitude <= this->circle->getRadius();
		}else{		//basso destra
			Vector2f diff = point2 - circleCenter;
			double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			return magnitude <= this->circle->getRadius();
		}
	}else if (circleCenter.x < point0.x){
		if (circleCenter.y < point0.y){	//alto-destra
			Vector2f diff = point0 - circleCenter;
			double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			return magnitude <= this->circle->getRadius();
		}else{		//basso destra
			Vector2f diff = point3 - circleCenter;
			double magnitude = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			return magnitude <= this->circle->getRadius();
		}
	}

	return false;
}

CircleCollisionMask::~CircleCollisionMask() {}

} /* namespace mask */
