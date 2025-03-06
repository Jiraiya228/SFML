#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"


class Player : public Entity
{
public:
	Player();
	~Player();

	void initialize() override;
	void draw(sf::RenderWindow& window) override;

	void move();
	void update();



private:

};
