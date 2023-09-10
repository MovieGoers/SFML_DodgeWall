#include "Collision.hpp"

bool Collision::CheckRectOverlap(const sf::Sprite s, std::vector<sf::RectangleShape> walls) {
	if (walls.size() == 0)
		return false;
	return s.getGlobalBounds().intersects(walls[0].getGlobalBounds());
}