#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	
	Класс который работтает как игровой движок

*/

class Game
{
private:
	//Переменные
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	//Приватные функции
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

