#include "World.hpp"
#include <iostream>

World::World(){
	_wallSize = sf::Vector2f(WALL_INITIAL_WIDTH, 30.f);
	_wallSpeed = WALL_SPEED;
	_wallSpawnTime = WALL_INITIAL_SPAWN_TIME;

	_score = 0;

	if (!_font.loadFromFile(SCORE_FONT_FILEPATH)) {
		std::cout << "Load Font Error\n";
	}

	_scoreText.setFont(_font);
	_scoreText.setCharacterSize(SCORE_TEXT_SIZE);
	_scoreText.setPosition(0, 0);
	_scoreText.setFillColor(sf::Color::White);

	_scoreText.setString(std::to_string(_score));
}

World::~World(){}

void World::MakeWall() {
	sf::RectangleShape temp_rect;
	temp_rect.setFillColor(sf::Color::Red);
	temp_rect.setOrigin(sf::Vector2f(_wallSize.x / 2, _wallSize.y / 2));
	temp_rect.setSize(_wallSize);
	temp_rect.setPosition(rand() % (WORLD_BOUNDARY_RIGHT - WORLD_BOUNDARY_LEFT) + WORLD_BOUNDARY_LEFT, 0.f);
	_walls.push_back(temp_rect);
}

void World::Update(float dt) {
	int walls_size = _walls.size();
	for (int i = 0; i < walls_size; i++) {
		sf::Vector2f tempWallPosition = _walls[i].getPosition();
		if (tempWallPosition.y > WINDOW_HEIGHT) {
			_walls.erase(_walls.begin());
			_score++;
			_scoreText.setString(std::to_string(_score));
			std::cout << "SCORE : " << _score << '\n';
		}	
		else
			_walls[i].setPosition(tempWallPosition + sf::Vector2f(0, _wallSpeed) * dt);
	}
}

void World::Draw(sf::RenderWindow* window) {
	window->draw(_scoreText);

	int walls_size = _walls.size();
	for (int i = 0; i < walls_size; i++) {
		window->draw(_walls[i]);
	}
}

float World::GetWallSpawnTime() {
	return _wallSpawnTime;
}