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

private:
	sf::Clock clockForMovement;
	sf::Clock ClockForView;

	sf::RectangleShape view;
	sf::RectangleShape collisionChecker;

	bool inView = false;

	float timeForMovement;
	int randNumForMovement;
};