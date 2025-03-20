#include "Map.h"
#include <iostream>

Map::Map() : tileWidth(32), tileHeight(32), totalTilesX(0), totalTilesY(0)
{
	initialize();
	load();
}

Map::~Map() {}

void Map::initialize() // ����� 
{
	// ������ ����!! ��� � ���������
	firstLayer[0] = "0000000000000000000000000000000000000000000000000";
	firstLayer[1] = "0                                               0";
	firstLayer[2] = "0                       0000                    0";
	firstLayer[3] = "0                                               0";
	firstLayer[4] = "0          0                                    0";
	firstLayer[5] = "0      E   0       0000       0000              0";
	firstLayer[6] = "0          0                                    0";
	firstLayer[7] = "0          0                                    0";
	firstLayer[8] = "0                                               0";
	firstLayer[9] = "0                               0000            0";
	firstLayer[10] = "0                                               0";
	firstLayer[11] = "0       0                                       0";
	firstLayer[12] = "0       0         0000            0             0";
	firstLayer[13] = "0       0                         0             0";
	firstLayer[14] = "0       0                         0             0";
	firstLayer[15] = "0                                 0             0";
	firstLayer[16] = "0                                               0";
	firstLayer[17] = "0            0000                               0";
	firstLayer[18] = "0                           E      0000         0";
	firstLayer[19] = "0                                               0";
	firstLayer[20] = "0                                               0";
	firstLayer[21] = "0                   0                           0";
	firstLayer[22] = "0       0000        0           0000            0";
	firstLayer[23] = "0                   0                           0";
	firstLayer[24] = "0                   0                           0";
	firstLayer[25] = "0                                               0";
	firstLayer[26] = "0      0                                        0";
	firstLayer[27] = "0      0           E         0000               0";
	firstLayer[28] = "0      0                                        0";
	firstLayer[29] = "0      0                            0000        0";
	firstLayer[30] = "0               0000                            0";
	firstLayer[31] = "0                                               0";
	firstLayer[32] = "0                                0              0";
	firstLayer[33] = "0                                0              0";
	firstLayer[34] = "0                                0              0";
	firstLayer[35] = "0          0000                  0              0";
	firstLayer[36] = "0                        E                      0";
	firstLayer[37] = "0                                               0";
	firstLayer[38] = "0                                      0        0";
	firstLayer[39] = "0                                      0        0";
	firstLayer[40] = "0                    0                 0        0";
	firstLayer[41] = "0      0000          0                 0        0";
	firstLayer[42] = "0                    0                          0";
	firstLayer[43] = "0                    0                          0";
	firstLayer[44] = "0                                               0";
	firstLayer[45] = "0                        E         0000         0";
	firstLayer[46] = "0           0000                                0";
	firstLayer[47] = "0                                               0";
	firstLayer[48] = "0                                               0";
	firstLayer[49] = "0000000000000000000000000000000000000000000000000";


}

void Map::load()
{
	layerLoad(firstLayer);
}

void Map::layerLoad(sf::String layer[])
{
	for (int i = 0; i < mapHeight; i++) // ���������� �� ��������
		for (int j = 0; j < mapWidth; j++) // � ��� �� ������
		{
			switch (layer[i][j])
			{
			case('0'): // ���
				createHitbox(tileWidth, tileHeight, j * tileWidth, i * tileHeight);
				break;
			case('E'): // ����
				enemiesPositions.push_back(sf::Vector2f(j * tileWidth, i * tileHeight));
				break;
			}
		}
}

void Map::update() // �������������� ������ � �����
{

}

void Map::createHitbox(int x, int y, int posX, int posY)
{
	std::cout << "CreateHitbox Working!" << std::endl;
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);
	hitbox.setSize(sf::Vector2f(x, y));
	hitbox.setPosition(posX, posY);
	mapHitbox.push_back(hitbox);
}

// ��������� ������� ���� �����
void Map::drawFirstLayer(sf::RenderWindow& window)
{
	for (const auto& hitbox : mapHitbox)
		window.draw(hitbox);
}


sf::Vector2f Map::getEnemyStartPosition()
{
	if (!enemiesPositions.empty())
	{
		sf::Vector2f enemyPosition = enemiesPositions.front();
		enemiesPositions.erase(enemiesPositions.begin());
		return enemyPosition;
	}
}
