#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	sf::CircleShape movingCircle;
	sf::CircleShape leftrightCircle;
	sf::RectangleShape player;
	sf::Font font;
	sf::Text speedometer;

	float leftrightSpeed = 50;
	float circleSpeed = 100;
	float playerSpeed = 100;
	bool xPositive = true;
	bool yPositive = true;
};