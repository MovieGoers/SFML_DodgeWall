#pragma once
#include <SFML/Graphics.hpp>
#include "Window.hpp"

class Game
{
	Window _window;
	sf::Time _elapsed;
	sf::Clock _clock;

public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartTime();
};