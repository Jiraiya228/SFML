#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Enemy1.h"
#include "Map.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing Ball with Chipmunk2D");
	window.setFramerateLimit(60);

	sf::Clock clockForSpawn; // òàéìåð äëÿ ñîçäàíèÿ âðàãîâ

	Player player;
	Map map;
	std::vector<Enemy1> enemyVector;

	for (size_t i = 0; i < 5; i++)
	{
		Enemy1 enemy1(map);
		enemyVector.push_back(enemy1);
	}


	// èíòåðâàë ñïàâíà âðàãîâ
	const float spawnInterval = 2.0f; // èíòåðâàë ñïàâíà âðàãîâ â ñåêóíäàõ
	clockForSpawn.restart(); // Çàïóñê òàéìåðà ñïàâíà

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		static int enemyCount = 0; // ïðåäåë îáðàáîòêè âðàãîâ

		if (clockForSpawn.getElapsedTime().asSeconds() >= spawnInterval && enemyCount < enemyVector.size())
		{
			clockForSpawn.restart();
			// 			if (enemyVector[enemyCount].getEnemyIsDead()) // óäàëåíèå âðàãà, åñëè îí óìåð
			// 				enemyVector.erase(enemyVector.begin() + enemyCount);
			enemyCount++; // åñëè òàéìåð ñðàáîòàë, òî ïðåäåë ñòàë âûøå
		}

		player.update(map);

		for (size_t i = 0; i < enemyCount; i++)
		{
			enemyVector[i].update(player, map);
		}

		map.update();

		window.clear(sf::Color::Black);
		player.draw(window);


		for (size_t i = 0; i < enemyCount; i++)
		{
			enemyVector[i].draw(window);
		}
		map.drawFirstLayer(window);
		window.display();
	}
	return 0;
}