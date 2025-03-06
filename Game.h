#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	
	����� ������� ��������� ��� ������� ������

*/

class Game
{
private:
	//����������
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	//��������� �������
	void initVariables();
	void initWindow();
	
public:
	//Constructor / destructor
	Game();
	virtual ~Game();

	//Function
	void update();
	void render();
	


};

