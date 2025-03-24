#include "Player.h"
#include <cmath>

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
	hitbox.setPosition(320, 160);

	cameraHitbox.setOrigin(640, 360);
	cameraHitbox.setSize(sf::Vector2f(1280, 720));
	cameraHitbox.setFillColor(sf::Color::Transparent);
	cameraHitbox.setOutlineColor(sf::Color::Magenta);
	cameraHitbox.setOutlineThickness(2);
}

void Player::move(Map& map)
{
	isMovingUp = false;
	isMovingDown = false;
	isMovingRight = false;
	isMovingLeft = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isMovingDown)
	{
		hitbox.move(0, -3 * speed);
		isMovingUp = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isMovingRight)
	{
		hitbox.move(-3 * speed, 0);
		isMovingLeft = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isMovingUp)
	{
		hitbox.move(0, 3 * speed);
		isMovingDown = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isMovingLeft)
	{
		hitbox.move(3 * speed, 0);
		isMovingRight = true;
	}

	// 	{
	// 		system("cls");
	// 		std::cout << "W - " << isMovingUp << " A - " << isMovingLeft << " S - " << isMovingDown << " D - " << isMovingRight << std::endl;
	// 		std::cout << direction.x << " - " << direction.y;
	// 		std::cout << "\nUP - " << upCollision << " DOWN - " << downCollision << " RIGHT - " << rightCollision << " LEFT - " << leftCollision << std::endl;
	// 	}

}

void Player::collisions(Map& map)
{
	sf::FloatRect playerRect = hitbox.getGlobalBounds();
	const float tolerance = 2.0f; // Если пересечение меньше 2 пикселей, игнорируем его

	upCollision = false;
	downCollision = false;
	leftCollision = false;
	rightCollision = false;

	// X
	for (const auto& mapHitbox : map.mapHitbox)
	{
		sf::FloatRect obstacleRect = mapHitbox.getGlobalBounds();
		sf::FloatRect intersection;
		if (playerRect.intersects(obstacleRect, intersection))
		{
			// Если пересечение по оси X меньше, чем по Y, обрабатываем горизонтально
			if (intersection.width < intersection.height && intersection.width > tolerance)
			{
				if (playerRect.left < obstacleRect.left)
				{
					hitbox.move(-intersection.width, 0);
					rightCollision = true;
				}
				else
				{
					hitbox.move(intersection.width, 0);
					leftCollision = true;
				}
				playerRect = hitbox.getGlobalBounds();
			}
		}
	}

	// Y
	// Обновляем playerRect после горизонтальной коррекции
	playerRect = hitbox.getGlobalBounds();
	for (const auto& mapHitbox : map.mapHitbox)
	{
		sf::FloatRect obstacleRect = mapHitbox.getGlobalBounds();
		sf::FloatRect intersection;
		if (playerRect.intersects(obstacleRect, intersection))
		{
			if (intersection.height < intersection.width && intersection.height > tolerance)
			{
				if (playerRect.top < obstacleRect.top)
				{
					hitbox.move(0, -intersection.height);
					downCollision = true;
				}
				else
				{
					hitbox.move(0, intersection.height);
					upCollision = true;
				}
				playerRect = hitbox.getGlobalBounds();
			}
		}
	}
}


void Player::update(Map& map)
{
	collisions(map);
	move(map);

	view = camera(view);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(hitbox);
	window.setView(view);
}

sf::View Player::camera(sf::View view)
{
	int offset = 10;

	float leftBorder = view.getCenter().x - offset;
	float rightBorder = view.getCenter().x + offset;

	float upBorder = view.getCenter().y - offset;
	float downBorder = view.getCenter().y + offset;

	float smoothFactor = 0.1f;

	// Позиция игрока
	float playerX = hitbox.getPosition().x;
	float cameraX = view.getCenter().x;

	float playerY = hitbox.getPosition().y;
	float cameraY = view.getCenter().y;

	if (playerX < leftBorder)
	{
		cameraX = playerX + offset;
	}
	else if (playerX > rightBorder)
	{
		cameraX = playerX - offset;
	}

	if (playerY < upBorder)
	{
		cameraY = playerY + offset;
	}
	else if (playerY > downBorder)
	{
		cameraY = playerY - offset;
	}

	float newCameraX = cameraX * smoothFactor + view.getCenter().x * (1 - smoothFactor);
	float newCameraY = cameraY * smoothFactor + view.getCenter().y * (1 - smoothFactor);

	cameraHitbox.setPosition(hitbox.getPosition());
	view.setSize(640, 360);

	view.setCenter(newCameraX, newCameraY); // Камера двигается только по X

	return view;
}