#include "Window.hpp"

Window::Window() { Setup("Window", sf::Vector2u(640, 480)); }

Window::Window(const std::string& l_title, const sf::Vector2u& l_size){
	Setup(l_title, l_size);
}

Window::~Window() { Destroy(); }

void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size) {
	_windowTitle = l_title;
	_windowSize = l_size;
	_isFullScreen = false;
	_isDone = false;
	Create();

	_isFocused = true;
	
	_eventManager.AddCallback("Fullscreen_toggle", &Window::ToggleFullScreen, this);
	_eventManager.AddCallback("Window_close", &Window::Close, this);
}

void Window::Destroy() {
	_window.close();
}

void Window::Create() {
	auto style = (_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	_window.create({ _windowSize.x, _windowSize.y, 32 }, _windowTitle, style);
}

void Window::Update() {
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			_isFocused = false;
			_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			_isFocused = true;
			_eventManager.SetFocus(true);
		}
		_eventManager.HandleEvent(event);
	}
	_eventManager.Update();
}

void Window::ToggleFullScreen(EventDetails* details) {
	_isFullScreen = !_isFullScreen;
	Destroy();
	Create();
}

void Window::BeginDraw() { _window.clear(sf::Color::Black); }

void Window::EndDraw() { _window.display(); }

bool Window::IsDone() { return _isDone; }

bool Window::IsFullScreen() { return _isFullScreen; }

sf::Vector2u Window::GetWindowSize() { return _windowSize; }

void Window::Draw(sf::Drawable& l_drawable) {
	_window.draw(l_drawable);
}

sf::RenderWindow& Window::GetWindow() {
	return _window;
}

void Window::Close(EventDetails* details) { _isDone = true; }

bool Window::IsFocused() {
	return _isFocused;
}
EventManager* Window::GetEventManager() {
	return &_eventManager;
}