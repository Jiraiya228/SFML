#include "Player.h"

Player::Player()
{
	initialize();
}

Player::~Player()
{
}

void Player::initialize()
{
	speed = 1.0f;
	widht = 32.0f;
	height = 32.0f;
	hitboxColor = sf::Color::Green;

	hitbox = sf::RectangleShape(sf::Vector2f(widht, height));
	hitbox.setFillColor(hitboxColor);
	hitbox.setPosition(400, 300);
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		hitbox.move(0, -3 * speed);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		hitbox.move(-3 * speed, 0);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		hitbox.move(0, 3 * speed);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		hitbox.move(3 * speed, 0);
	}
}

void Player::update()
{
	move();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(hitbox);
}