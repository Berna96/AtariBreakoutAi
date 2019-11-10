/*
 * Menu.h
 *
 *  Created on: 26 lug 2019
 *      Author: Berna
 */

#ifndef MENU_MENU_H_
#define MENU_MENU_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "../GameObject.h"

namespace menu {

class Menu : public GameObject{
private:
	/*Attenzione: font e text devono essere dichiarate e istanziate
	 * (NO PUNTATORI) insieme! Se no non va window.draw()
	 * */
	sf::Text text;
	sf::Font font;
public:
	Menu();
	void update(sf::Keyboard::Key& );
	void draw(sf::RenderWindow&);
	virtual ~Menu();
};

} /* namespace menu */

#endif /* MENU_MENU_H_ */
