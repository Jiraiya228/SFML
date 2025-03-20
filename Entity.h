#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
public:
	Entity();
	~Entity();

	virtual void initialize() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::RectangleShape getHitbox();
	sf::Vector2f getHitboxPosition();
	sf::Vector2f NormalizeVector(sf::Vector2f vector);
protected:
	sf::Vector2f direction;

	sf::RectangleShape hitbox;
	sf::Color hitboxColor;

	float height;
	float widht;
	float speed;

	bool isMovingUp = false;
	bool isMovingDown = false;
	bool isMovingRight = false;
	bool isMovingLeft = false;

	bool upCollision = false;
	bool downCollision = false;
	bool rightCollision = false;
	bool leftCollision = false;
};