#include "Game.hpp"

Game::Game() : _window("Game", sf::Vector2u(800, 600)) {
	// ���� ��� ����
}

Game::~Game() {
	// ���� ��� ����
}

void Game::HandleInput() {
	// Input ����.
}

void Game::Update() {
	_window.Update(); 
	// ���� �� ��� ������Ʈ �� �̺�Ʈ ����.
}

void Game::Render() {
	// Clear -> Draw -> DIsplay Cycle.
	_window.BeginDraw();	// Clear
	
	// _window.Draw(something);

	_window.EndDraw();		// DIsplay
}

Window* Game::GetWindow() {
	return &_window;
}

sf::Time Game::GetElapsed() {
	return _elapsed;
}

void Game::RestartTime() {
	_elapsed = _clock.restart();
}
