#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"

class World
{
	std::vector<sf::RectangleShape> _walls;

	sf::Vector2f _wallSize;
	float _wallSpeed;
	float _wallSpawnTime;

	int _score;

	sf::Font _font;
	sf::Text _scoreText;
	
public:
	World();
	~World();

	void MakeWall();
	float GetWallSpawnTime();

	void Setup();
	void Update(float dt);
	void Draw(sf::RenderWindow *window);

	std::vector<sf::RectangleShape> GetWalls();
};

