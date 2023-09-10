#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.hpp"
#include "Player.hpp"

class Window {
	sf::RenderWindow _window;
	sf::Vector2u _windowSize;
	std::string _windowTitle;

	EventManager _eventManager;

	bool _isDone;
	bool _isFullScreen;
	bool _isFocused;

	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();

public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();

	void BeginDraw();						// Draw 이전 호출 (Clear)
	void EndDraw();							// Draw 이후 호출 (Display)

	void Update();							// 각 프레임 당 Update

	bool IsDone();
	bool IsFullScreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullScreen(EventDetails* details);

	void Draw(sf::Drawable& l_drawable);

	sf::RenderWindow& GetWindow();

	bool IsFocused();
	EventManager* GetEventManager();
	void Close(EventDetails* details = nullptr);
	
};