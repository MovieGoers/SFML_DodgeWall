#include "Game.hpp"
#include "config.hpp"

Game::Game() : _window("Game", sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)) {
	// 게임 요소 세팅
	_window.GetEventManager()->AddCallback("Player_move_left", &Game::MovePlayerLeft, this);
	_window.GetEventManager()->AddCallback("Player_move_right", &Game::MovePlayerRight, this);
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
	_player.Update(_elapsed.asSeconds());	
}

void Game::Render() {
	// Clear -> Draw -> DIsplay Cycle.
	_window.BeginDraw();	// Clear
	
	// _window.Draw(something);
	_window.Draw(_player.GetSprite());
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

void Game::MovePlayerLeft(EventDetails* details) {
	_player.MoveLeft();
}

void Game::MovePlayerRight(EventDetails* details) {
	_player.MoveRight();
}
