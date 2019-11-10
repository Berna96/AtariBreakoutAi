/*
 * Menu.cpp
 *
 *  Created on: 26 lug 2019
 *      Author: Berna
 */

#include "Menu.h"
#include "../GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <iostream>
#include <stdexcept>
#include "../game.h"
using namespace std;
using namespace sf;

namespace menu {

Menu::Menu() {
	string str_text = "Breakout AI\nPress P for play Breakout\nPress C for play CPU";
	if (!font.loadFromFile("ARIAL.TTF"))
	{
	    throw new std::exception();
	}
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString(str_text);
	// set the character size
	text.setCharacterSize(36); // in pixels, not points!
	// set the color
	text.setFillColor(sf::Color::White);

}

void Menu::update(Keyboard::Key& key){
	if (key == Keyboard::Key::P){
		GameUtils::CURRENT_STATE = GameUtils::gamestates::GAME_INIT_PLAYER;
		//std::cout << "P";
	}
	if (key == Keyboard::Key::C){
		GameUtils::CURRENT_STATE = GameUtils::gamestates::GAME_INIT_CPU;
		//std::cout << "C";
	}
}

void Menu::draw(sf::RenderWindow& window){
	window.draw(text);
}

Menu::~Menu(){}

} /* namespace menu */
