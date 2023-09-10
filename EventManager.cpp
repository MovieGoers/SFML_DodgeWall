#include "EventManager.hpp"

EventManager::EventManager() : _hasFocus(true) { LoadBinding(); }

EventManager::~EventManager() {
	for (auto &itr : _bindings) {
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding *binding) {
	if (_bindings.find(binding->_name) != _bindings.end())
		return false;

	return _bindings.emplace(binding->_name, binding).second;
}

bool EventManager::RemoveBinding(std::string name) {
	auto itr = _bindings.find(name);

	if (itr == _bindings.end()) { return false; }

	delete itr->second;
	_bindings.erase(itr);
	return true;
}

void EventManager::HandleEvent(sf::Event& event) {
	// SFML 이벤트 관리.

	//bindings의 모든 binding을 탐색.
	for (auto& b_itr : _bindings) {
		Binding* bind = b_itr.second;

		// 각 binding의 모든 event를 탐색.
		for (auto& e_itr : bind->_events) {
			EventType sfmlEvent = (EventType)event.type;

			if (e_itr.first != sfmlEvent) { continue; }

			// event의 타입(sfmlEvent)이 키보드 이벤트와 일치하는지 확인.
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {

				// 일치하는 경우 binding의 키코드와 event의 키코드와 일치하는지 확인.
				if (e_itr.second._code == event.key.code) {
					// keycode의 일치.
					// C count 증가.
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = e_itr.second._code;
					}

					++(bind->c);

					break;
				}
			}
			// event의 타입(sfmlEvent)이 마우스 이벤트와 일치하는지 확인.
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				// 일치하는 경우 binding의 키코드와 event의 키코드와 일치하는지 확인.
				if (e_itr.second._code == event.mouseButton.button) {
					// keycode의 일치.
					// C count 증가.
					bind->_details._mouse.x = event.mouseButton.x;
					bind->_details._mouse.y = event.mouseButton.y;
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = e_itr.second._code;
					}
					++(bind->c);
					break;
				}
			}
			else {
				if (sfmlEvent == EventType::MouseWheel) {
					bind->_details._mouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind->_details._size.x = event.size.width;
					bind->_details._size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->_details._textEntered = event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}

// 실시간 input 확인 및 Binding 업데이트.
void EventManager::Update() {
	if (!_hasFocus) { return; }

	for (auto& b_itr : _bindings) {
		Binding* bind = b_itr.second;

		// 실시간 마우스, 키보드, 조이스틱 input 확인.
		for (auto& e_itr : bind->_events) {
			switch (e_itr.first) {
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second._code))) {
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = e_itr.second._code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second._code))) {
					if (bind->_details._keyCode != -1) {
						bind->_details._keyCode = e_itr.second._code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Joystick):
				// 추후에 추가.
				break;
			}
		}

		// Binding의 이벤트 개수와 실제로 Binding에서 발생한 이벤트 개수가 같은지 확인. (즉, Binding된 모든 이벤트가 발생하였는지 확인)
		if (bind->_events.size() == bind->c) {
			auto callItr = _callbacks.find(bind->_name);
			if (callItr != _callbacks.end())
			{
				// 콜백 함수 실행.
				callItr->second(&bind->_details);
			} 
		}
		bind->c = 0;
		bind->_details.Clear();
	}
}

void EventManager::LoadBinding() {
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("keys.cfg");
	if (!bindings.is_open()) {
		std::cout << "CANNOT OPEN keys.cfg." << '\n';
		return;
	}

	std::string line;

	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);

		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) {
				delete bind;
				bind = nullptr;
				break;
			}

			EventType type = EventType(stoi(keyval.substr(start, end - start)));

			int code = stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo._code = code;

			bind->BindEvent(type, eventInfo);
		}

		if (!AddBinding(bind)) {delete bind; }
		bind = nullptr;
	}
	bindings.close();
}

void EventManager::SetFocus(const bool& focus) {
	_hasFocus = focus;
}