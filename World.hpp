#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"

class World
{
	std::vector<sf::RectangleShape> _walls;

	sf::Vector2f _wallSize;
	float _wallSpeed;
	float _wallSpawnTime;
	
public:
	World();
	~World();

	void MakeWall();

	void Update(float dt);
	void Draw(sf::RenderWindow *window);
};

