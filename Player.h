#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Map.h"

class Map;

class Player : public Entity
{
public:
	Player();
	~Player();

	void initialize() override;
	void draw(sf::RenderWindow& window) override;
	void collisions(Map& map);

	void move(Map& map);
	void update(Map& map);
	sf::View camera(sf::View view);
private:
	sf::RectangleShape cameraHitbox;
	sf::View view;
};