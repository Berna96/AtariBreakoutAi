/*
 * GameOver.h
 *
 *  Created on: 19 ott 2019
 *      Author: Berna
 */

#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "GameObject.h"
#include <string.h>

class GameOver: public GameObject {
private:
	std::string str_text;
	sf::Text text;
	sf::Font font;
	bool ai;
public:
	GameOver(bool);
	virtual void update(sf::Keyboard::Key&);
	virtual void onCollisionEnter(const GameObject*){};
	//virtual bool collideWith(const GameObject*){return false;};
	virtual void draw(sf::RenderWindow&);
	virtual ~GameOver();
};

#endif /* GAMEOVER_H_ */
