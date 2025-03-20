#include "Enemy1.h"
#include <cstdlib>
#include <stdlib.h> 

Enemy1::Enemy1(Map& map)
{
	initialize();
	hitbox.setPosition(map.getEnemyStartPosition());
}

Enemy1::~Enemy1()
{
}

void Enemy1::initialize()
{
	speed = 0.7f;
	widht = 32.0f;
	height = 32.0f;
	hitboxColor = sf::Color::Red;

	hitbox = sf::RectangleShape(sf::Vector2f(widht, height));
	hitbox.setFillColor(hitboxColor);
	hitbox.setPosition(200, 150);

	collisionChecker.setSize(sf::Vector2f(64, 64));
	collisionChecker.setFillColor(sf::Color::Transparent);
	collisionChecker.setOutlineColor(sf::Color::Yellow);
	collisionChecker.setOutlineThickness(2);

	timeForMovement = 3.0f;
}


void Enemy1::move(Player& player)
{
	isMovingUp = false;
	isMovingLeft = false;
	isMovingDown = false;
	isMovingRight = false;

	if (clockForMovement.getElapsedTime().asSeconds() > timeForMovement)
	{
		randNumForMovement = std::rand() % 4 + 1;
		clockForMovement.restart();
	}

	if (inView)
	{
		sf::Vector2f direction = player.getHitboxPosition() - hitbox.getPosition();
	}

	switch (randNumForMovement)
	{
	case 1:
		if (!upCollision)
		{
			hitbox.move(0, -3 * speed);
			isMovingUp = true;
			break;
		}
		else
		{
			randNumForMovement = std::rand() % 4 + 1;
			if (randNumForMovement == 1)
				randNumForMovement = 3; break;
		}

	case 2:
		if (!leftCollision)
		{
			hitbox.move(-3 * speed, 0);
			isMovingLeft = true;
			break;
		}
		else
		{
			randNumForMovement = std::rand() % 4 + 1;
			if (randNumForMovement == 2)
				randNumForMovement = 4; break;
		}
	case 3:
		if (!downCollision)
		{
			hitbox.move(0, 3 * speed);
			isMovingDown = true;
			break;
		}
		else
		{
			randNumForMovement = std::rand() % 4 + 1;
			if (randNumForMovement == 3)
				randNumForMovement = 1; break;
		}
	case 4:
		if (!rightCollision)
		{
			hitbox.move(3 * speed, 0);
			isMovingRight = true;
			break;
		}
		else
		{
			randNumForMovement = std::rand() % 4 + 1;
			if (randNumForMovement == 4)
				randNumForMovement = 2; break;
		}
	default:
		break;
	}

	std::cout << "\nUP - " << upCollision << " DOWN - " << downCollision << " RIGHT - " << rightCollision << " LEFT - " << leftCollision << std::endl;
}

void Enemy1::collisions(Map& map)
{
	collisionChecker.setPosition(hitbox.getPosition().x - 18, hitbox.getPosition().y - 18);

	upCollision = false;
	downCollision = false;
	leftCollision = false;
	rightCollision = false;

	for (const auto& mapHitbox : map.mapHitbox)
	{
		sf::FloatRect obstacleRect = mapHitbox.getGlobalBounds();
		sf::FloatRect intersection;

		if (collisionChecker.getGlobalBounds().intersects(obstacleRect, intersection))
		{
			//X
			if (intersection.width < intersection.height)
			{
				if (collisionChecker.getGlobalBounds().left < obstacleRect.left)
				{
					//right
					rightCollision = true;
				}
				else
				{
					//left
					leftCollision = true;
				}
			}
			else
			{
				//Y
				if (collisionChecker.getGlobalBounds().top < obstacleRect.top)
				{
					//down
					downCollision = true;
				}
				else
				{
					//up
					upCollision = true;
				}
			}
		}
	}
}

bool Enemy1::fieldOfView(Player& player)
{

	if (inView)
	{
		view.setSize(sf::Vector2f(192, 192));
		view.setPosition(hitbox.getPosition().x - 80, hitbox.getPosition().y - 80);
		view.setFillColor(sf::Color::Transparent);
		view.setOutlineColor(sf::Color::Red);
		view.setOutlineThickness(2);
	}

	else
	{
		view.setSize(sf::Vector2f(128, 128));
		view.setPosition(hitbox.getPosition().x - 48, hitbox.getPosition().y - 48);
		view.setFillColor(sf::Color::Transparent);
		view.setOutlineColor(sf::Color::Blue);
		view.setOutlineThickness(2);
	}

	if (view.getGlobalBounds().intersects(player.getHitbox().getGlobalBounds()))
	{
		inView = true;
		ClockForView.restart();
	}

	if (ClockForView.getElapsedTime().asSeconds() > 4)
	{
		inView = false;
	}

	return inView;
}

void Enemy1::update(Player& player, Map& map)
{
	collisions(map);
	move(player);
	fieldOfView(player);
}


void Enemy1::draw(sf::RenderWindow& window)
{
	window.draw(hitbox);
	window.draw(view);
	window.draw(collisionChecker);
}


// метод установки цели и обновления позиции
void Enemy1::setTargetPosition(const sf::Vector2f& position)
{
	targetPosition = position;
	movingToTarget = true;
}

void Enemy1::update()
{
	if (movingToTarget)
	{
		sf::Vector2f direction = targetPosition - getPosition();
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length > 1.f)
		{
			direction /= length;
			mSprite.move(direction * speed);
		}
		else
		{
			movingToTarget = false;
		}
	}
}

sf::Vector2f Enemy1::getPosition() const
{
	return mSprite.getPosition();
}