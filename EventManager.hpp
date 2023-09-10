#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>

enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo {
	EventInfo() { _code = 0; }
	EventInfo(int event) { _code = event; }
	union {
		int _code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
	EventDetails(const std::string& bindName) : _name(bindName) {
		Clear();
	}
	std::string _name;

	sf::Vector2i _size;
	sf::Uint32 _textEntered;
	sf::Vector2i _mouse;
	int _mouseWheelDelta;
	int _keyCode;

	void Clear() {
		_size = sf::Vector2i(0, 0);
		_textEntered = 0;
		_mouse = sf::Vector2i(0, 0);
		_mouseWheelDelta = 0;
		_keyCode = -1;
	}
};

struct Binding {
	Binding(const std::string& name) : _name(name), _details(name), c(0){}
	void BindEvent(EventType type, EventInfo info = EventInfo()) {
		_events.emplace_back(type, info);
	}

	Events _events;
	std::string _name;
	int c;				// 현재 일어나고 있는 이벤트 개수.

	EventDetails _details;
};

using Bindings = std::unordered_map<std::string, Binding*>;

using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

class EventManager
{
	void LoadBinding();

	Bindings _bindings;
	Callbacks _callbacks;
	bool _hasFocus;

public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding* binding);		
	bool RemoveBinding(std::string name);	
	void SetFocus(const bool& focus);

	template<class T>
	bool AddCallback(const std::string& name, void(T::* func)(EventDetails*), T* instance) { // 헤더에 정의.
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return _callbacks.emplace(name, temp).second;
	}

	void RemoveCallback(const std::string& name) { // 헤더에 정의.
		_callbacks.erase(name);
	}

	void HandleEvent(sf::Event& event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* wind = nullptr) {
		return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
	}
};

