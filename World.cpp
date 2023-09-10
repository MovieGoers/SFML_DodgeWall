#include "World.hpp"

World::World(){
	_wallSize = sf::Vector2f(WALL_INITIAL_WIDTH, 30.f);
	_wallSpeed = WALL_SPEED;
	_wallSpawnTime = WALL_INITIAL_SPAWN_TIME;
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
		_walls[i].setPosition(tempWallPosition + sf::Vector2f(0, _wallSpeed) * dt);
	}
}

void World::Draw(sf::RenderWindow* window) {
	int walls_size = _walls.size();
	for (int i = 0; i < walls_size; i++) {
		window->draw(_walls[i]);
	}
}