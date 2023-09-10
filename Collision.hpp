#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:
	bool CheckRectOverlap(const sf::Sprite s, std::vector<sf::RectangleShape> walls);
};

