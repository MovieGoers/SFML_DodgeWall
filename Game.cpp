#include "Game.hpp"

Game::Game() : _window("Game", sf::Vector2u(800, 600)) {
	// 게임 요소 세팅
}

Game::~Game() {
	// 게임 요소 정리
}

void Game::HandleInput() {
	// Input 관리.
}

void Game::Update() {
	_window.Update(); 
	// 게임 내 요소 업데이트 및 이벤트 관리.
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
