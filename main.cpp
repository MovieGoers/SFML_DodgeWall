#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main(int argc ,void** argv[]) {
	Game game;

	while (!game.GetWindow()->IsDone()) {
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartTime();
	}

	return 0;
}