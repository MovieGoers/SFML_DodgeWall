#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.hpp"
#include "config.hpp"
#include <iostream>

class Player
{
	sf::Texture _texture;
	sf::Sprite _sprite;

	float _speed;
	sf::Vector2f _position;
	sf::Vector2f _velocity;

public:
	Player();
	~Player();

	void MoveLeft();
	void MoveRight();

	void Update(float dt);
	sf::Sprite& GetSprite();
};

