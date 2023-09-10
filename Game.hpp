#pragma once
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Player.hpp"
#include <string>

class Game
{
	Window _window;
	sf::Time _elapsed;
	sf::Clock _clock;

	Player _player;

public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartTime();

	void MovePlayerLeft(EventDetails* details);
	void MovePlayerRight(EventDetails* details);
	void StopPlayerLeft(EventDetails* details);
	void StopPlayerRight(EventDetails* details);
};