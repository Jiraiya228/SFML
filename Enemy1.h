#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Player.h"

class Enemy1 : public Entity
{
public:
	Enemy1(Map& map);
	~Enemy1();

	void initialize() override;

	void draw(sf::RenderWindow& window) override;
	void collisions(Map& map);

	void move(Player& player);
	void update(Player& player, Map& map);
	bool fieldOfView(Player& player);

	void setTargetPosition(const sf::Vector2f& position);
	void update();

	sf::Vector2f getPosition() const;
	sf::Vector2f setPosition() const;

private:
	sf::Clock clockForMovement;
	sf::Clock ClockForView;

	sf::RectangleShape view;
	sf::RectangleShape collisionChecker;
	sf::Sprite mSprite;

	sf::Vector2f targetPosition;
	bool movingToTarget = false;
	float speed = 100.f; // Скорость врага

	bool inView = false;

	float timeForMovement;
	int randNumForMovement;
};