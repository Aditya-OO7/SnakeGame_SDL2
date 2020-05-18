#include"Game.h"

int main(int argc, char** argv) {

	Game game;

	game.initSystem();

	while (true)
	{
		
		game.inputThisFrame = false;

		game.processInput();
		game.UpdateGame();
	}
	return 0;
}