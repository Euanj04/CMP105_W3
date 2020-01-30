#include "Level.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	leftrightCircle.setRadius(30.0);
	leftrightCircle.setOrigin(leftrightCircle.getRadius(), leftrightCircle.getRadius());
	leftrightCircle.setFillColor(sf::Color::Blue);
	leftrightCircle.setPosition(10, 50);

	font.loadFromFile("font/arial.ttf");
	speedometer.setFont(font);
	speedometer.setPosition(20, 20);

	movingCircle.setRadius(30.0);
	movingCircle.setOrigin(movingCircle.getRadius(), movingCircle.getRadius());
	movingCircle.setFillColor(sf::Color::Red);
	movingCircle.setPosition(10, 50);

	player.setSize(sf::Vector2f(20, 20));
	player.setOrigin(10, 10);
	player.setPosition(100, 100);
	player.setFillColor(sf::Color::Yellow);
}

Level::~Level()
{

}
// handle user input
void Level::handleInput(float dt)
{
	
	if (input->isKeyDown(sf::Keyboard::W) && circleSpeed < 10000) {
		circleSpeed += (30*dt);
	}
	if (input->isKeyDown(sf::Keyboard::S) && circleSpeed > 0){
		circleSpeed -= (30*dt);
	}
	if (input->isKeyDown(sf::Keyboard::Up) && player.getPosition().y > 10) {
		player.move(0, -playerSpeed * dt);
	}
	if (input->isKeyDown(sf::Keyboard::Down) && player.getPosition().y < window->getSize().y - 10) {
		player.move(0, playerSpeed * dt);
	}
	if (input->isKeyDown(sf::Keyboard::Left) && player.getPosition().x > 10) {
		player.move(-playerSpeed * dt, 0);
	}
	if (input->isKeyDown(sf::Keyboard::Right) && player.getPosition().x < window->getSize().x - 10) {
		player.move(playerSpeed * dt, 0);
	}
}

// Update game objects
void Level::update(float dt)
{
	leftrightCircle.move(leftrightSpeed * dt, 0);
	if ((leftrightCircle.getRadius() > leftrightCircle.getPosition().x && signbit(leftrightSpeed)) || (leftrightCircle.getPosition().x > window->getSize().x - leftrightCircle.getRadius() && !signbit(leftrightSpeed))) {
		leftrightSpeed *= -1;
	}
	leftrightCircle.move(leftrightSpeed * dt, 0);
	if ((movingCircle.getRadius() > movingCircle.getPosition().x && !xPositive) || (movingCircle.getPosition().x > window->getSize().x - movingCircle.getRadius() && xPositive)) {
		xPositive = !xPositive;
	}
	if ((movingCircle.getRadius() > movingCircle.getPosition().y && !yPositive) || (movingCircle.getPosition().y > window->getSize().y - movingCircle.getRadius() && yPositive)) {
		yPositive = !yPositive;
	}

	if (xPositive) {
		movingCircle.move(circleSpeed*dt,0);
	}
	else {
		movingCircle.move(-circleSpeed*dt, 0);
	}
	if (yPositive) {
		movingCircle.move(0, circleSpeed*dt);
	}
	else {
		movingCircle.move(0, -circleSpeed*dt);
	}
	speedometer.setString(std::to_string(int(circleSpeed)));
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(leftrightCircle);
	window->draw(movingCircle);
	window->draw(player);
	window->draw(speedometer);
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}