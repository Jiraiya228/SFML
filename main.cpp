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

	sf::Clock clockForSpawn; // ������ ��� �������� ������

	Player player;
	Map map;
	std::vector<Enemy1> enemyVector;

	for (size_t i = 0; i < 5; i++)
	{
		Enemy1 enemy1(map);
		enemyVector.push_back(enemy1);
	}


	// �������� ������ ������
	const float spawnInterval = 2.0f; // �������� ������ ������ � ��������
	clockForSpawn.restart(); // ������ ������� ������

	std::vector<Enemy1> enemies; // Контейнер с врагами
	enemies.emplace_back(); // Добавление нового объекта в вектор
	enemies.back().setPosition(500.f, 300.f); // Доступ к последнему элементу и установка позиции

	enemies.emplace_back().setPosition(700.f, 400.f);

	// Определение зоны триггера (например, дверь или ключ)
	sf::FloatRect triggerZone(100.f, 100.f, 50.f, 50.f);
	bool triggerActivated = false;
	sf::Vector2f triggerPosition;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
		{
			if (player.isInteractingWith(triggerZone))
			{
				triggerActivated = true;
				triggerPosition = player.getPosition();
			}
		}
	

		static int enemyCount = 0; // ������ ��������� ������

		if (clockForSpawn.getElapsedTime().asSeconds() >= spawnInterval && enemyCount < enemyVector.size())
		{
			clockForSpawn.restart();
			// 			if (enemyVector[enemyCount].getEnemyIsDead()) // �������� �����, ���� �� ����
			// 				enemyVector.erase(enemyVector.begin() + enemyCount);
			enemyCount++; // ���� ������ ��������, �� ������ ���� ����
		}

		// Логика перемещения врагов
		if (triggerActivated)
		{
			for (Enemy1& enemy : enemies)
			{
				if (enemy.getPosition().x > triggerPosition.x - 200 &&
					enemy.getPosition().x < triggerPosition.x + 200 &&
					enemy.getPosition().y > triggerPosition.y - 200 &&
					enemy.getPosition().y < triggerPosition.y + 200)
				{
					enemy.setTargetPosition(triggerPosition);
				}
			}
			triggerActivated = false;
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

		// Отрисовка триггера (для теста, потом можно убрать)
		sf::RectangleShape triggerShape(sf::Vector2f(triggerZone.width, triggerZone.height));
		triggerShape.setPosition(triggerZone.left, triggerZone.top);
		triggerShape.setFillColor(sf::Color(255, 0, 0, 100)); // Полупрозрачный красный
		window.draw(triggerShape);
	}
	return 0;
}