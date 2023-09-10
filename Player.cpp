#include "Player.hpp"

Player::Player() {
	if (!_texture.loadFromFile(PLAYER_TEXTURE_FILEPATH)) {
		std::cout << "Player Textrue Loading Error!\n";
	}
	_speed = PLAYER_SPEED;
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().width / 2);
	_position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);
}

Player::~Player() {

}

void Player::Update(float dt) {
	//_position += _speed * _velocity * dt;
	_sprite.setPosition(_position);
}

sf::Sprite& Player::GetSprite() {
	return _sprite;
}

void Player::MoveLeft(){
	_velocity.x = -1;
}
void Player::MoveRight(){
	_velocity.x = +1;
}

void Player::Stop() {
	_velocity.x = 0;
}

sf::Vector2f Player::GetPosition() {
	return _position;
}

void Player::SetPosition(sf::Vector2f position) {
	_position = position;
}