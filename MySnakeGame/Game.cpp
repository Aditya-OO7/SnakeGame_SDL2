#include "Game.h"
#include"GameState.h"
#include"RenderGame.h"
#include"GameUI.h"

GameState gameState;
GameUI gameUI;

Game::Game()
{

	_window = nullptr;
	_renderer = nullptr;

	// tailLength is incremented every time the snake eats food
	tailLength = 0;

	// Size of tiles
	wscale = 24;
	hscale = 24;

	// Player position variables
	 x = 0;
	y = 0;
	prevX = 0;
	prevY = 0;

	// Movement controls
	up = false;
	down = false;
	right = false;
	left = false;

	inputThisFrame = false;
	redo = false;
	//Player Rect
	player.x = 0;
	player.y = 0;
	player.h = 0;
	player.w = 0;

	//Food Rect
	food.w = wscale;
	food.h = hscale;
	food.x = 0;
	food.y = 0;

}

Game::~Game()
{
	SDL_DestroyWindow(_window);

	TTF_Quit();

	SDL_Quit();
}

bool Game::isGameRunning()
{

	return true;
}

void Game::initSystem()
{
	foodLoc = getFoodSpawn(tailX, tailY, x, y, wscale, hscale, tailLength);
	food.x = foodLoc.first;
	food.y = foodLoc.second;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	_window = SDL_CreateWindow("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wscale * hscale + 1, wscale * hscale + 1, SDL_WINDOW_RESIZABLE);
		
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	timeX = SDL_GetTicks() / 100;

	speedT = gameUI.StartUI(_renderer, evnt,wscale);

}

void Game::processInput()
{
	newTime = SDL_GetTicks() / speedT; //This value (75) is the speed at which the blocks are updated
	delta = newTime - timeX;
	timeX = newTime;

	if (tailLength >= 575)
	{
		gameState.YouWin(_renderer, evnt, wscale, hscale, tailLength);
		x = 0;
		y = 0;
		up = false;
		left = false;
		right = false;
		down = false;
		tailX.clear();
		tailY.clear();
		tailLength = 0;
		redo = false;
		foodLoc = getFoodSpawn(tailX, tailY, x, y, wscale, hscale, tailLength);

		if (food.x == -100 && food.y == -100) {
			redo = true;
		}

		food.x = foodLoc.first;
		food.y = foodLoc.second;
	}

	if (SDL_PollEvent(&evnt)) {

		// Simply exit the program when told to
		if (evnt.type == SDL_QUIT) {
			exit(0);
		}

		// If a key is pressed
		if (evnt.type == SDL_KEYDOWN && inputThisFrame == false) {

			// Then check for the key being pressed and change direction accordingly
			if (down == false && evnt.key.keysym.scancode == SDL_SCANCODE_UP) {
				up = true;
				left = false;
				right = false;
				down = false;
				inputThisFrame = true;
			}
			else if (right == false && evnt.key.keysym.scancode == SDL_SCANCODE_LEFT) {
				up = false;
				left = true;
				right = false;
				down = false;
				inputThisFrame = true;
			}
			else if (up == false && evnt.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				up = false;
				left = false;
				right = false;
				down = true;
				inputThisFrame = true;
			}
			else if (left == false && evnt.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
				up = false;
				left = false;
				right = true;
				down = false;
				inputThisFrame = true;
			}

		}

	}

}

void Game::UpdateGame()
{
	prevX = x;
	prevY = y;

	if (up) {
		y -= delta * wscale;
	}
	else if (left) {
		x -= delta * wscale;
	}
	else if (right) {
		x += delta * wscale;
	}
	else if (down) {
		y += delta * wscale;
	}

	if (redo == true) {

		redo = false;
		foodLoc = getFoodSpawn(tailX, tailY, x, y, wscale, hscale, tailLength);
		food.x = foodLoc.first;
		food.y = foodLoc.second;

		if (food.x == -100 && food.y == -100) {
			redo = true;
		}

	}

	// Collision detection, has played collided with food?
	if ( checkCollision() ) {

		// Spawn new food after it has been eaten
		foodLoc = getFoodSpawn(tailX, tailY, x, y, wscale, hscale, tailLength);
		food.x = foodLoc.first;
		food.y = foodLoc.second;

		if (food.x == -100 && food.y == -100) {
			redo = true;
		}

		tailLength++;
	}

	if (delta * wscale == 24) {

		// Update tail size and position
		if (tailX.size() != tailLength) {
			tailX.push_back(prevX);
			tailY.push_back(prevY);
		}

		//Loop through every tail block, move all blocks to the nearest block in front
		//This updates the blocks from end (farthest from player block) to the start (nearest to player block)
		for (int i = 0; i < tailLength; i++) {

			if (i > 0) {
				tailX[i - 1] = tailX[i];
				tailY[i - 1] = tailY[i];
			}

		}

		if (tailLength > 0) {
			tailX[tailLength - 1] = prevX;
			tailY[tailLength - 1] = prevY;
		}

	}
	for (int i = 0; i < tailLength; i++) {

		if (x == tailX[i] && y == tailY[i]) {
			gameState.GameOver(_renderer, evnt, wscale, hscale, tailLength);
			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;
			redo = false;

			foodLoc = getFoodSpawn(tailX, tailY, x, y, wscale, hscale, tailLength);
			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			food.x = foodLoc.first;
			food.y = foodLoc.second;
		}

	}

	if (x < 0 || y < 0 || x > wscale* hscale - wscale || y > wscale* hscale - wscale) {
		gameState.GameOver(_renderer, evnt, wscale, hscale, tailLength);
		x = 0;
		y = 0;
		up = false;
		left = false;
		right = false;
		down = false;
		tailX.clear();
		tailY.clear();
		tailLength = 0;
		redo = false;
		foodLoc = getFoodSpawn(tailX, tailY, x, y, wscale, hscale, tailLength);
		food.x = foodLoc.first;
		food.y = foodLoc.second;

		if (food.x == -100 && food.y == -100) {
			redo = true;
		}

	}

	RenderGame renderGame;

	renderGame.renderFood(_renderer, food);
	renderGame.renderPlayer(_renderer, player, x, y, wscale, tailX, tailY, tailLength);
	renderGame.renderScore(_renderer, tailLength, wscale, hscale);

	SDL_RenderDrawLine(_renderer, 0, 0, 0, 24 * 24);
	SDL_RenderDrawLine(_renderer, 0, 24 * 24, 24 * 24, 24 * 24);
	SDL_RenderDrawLine(_renderer, 24 * 24, 24 * 24, 24 * 24, 0);
	SDL_RenderDrawLine(_renderer, 24 * 24, 0, 0, 0);

	// Put everything on screen
		// Nothing is actually put on screen until this is called
	SDL_RenderPresent(_renderer);

	// Choose a color and fill the entire window with it, this resets everything before the next frame
	// This also give us the background color
	SDL_SetRenderDrawColor(_renderer, 105, 105, 105, 255);
	SDL_RenderClear(_renderer);

}

bool Game::checkCollision()
{

	if (x == food.x && y == food.y) {
		return true;
	}

	return false;
}

pair<int, int> Game::getFoodSpawn(vector<int> tailX, vector<int> tailY, int playerX, int playerY, int wscale, int hscale, int tailLength)
{
	bool valid = false;
	int x = 0;
	int y = 0;
	srand(time(0));
	x = hscale * (rand() % wscale);
	y = hscale * (rand() % wscale);
	valid = true;

	// Check all tail blocks and player block
	for (int i = 0; i < tailLength; i++) {

		if ((x == tailX[i] && y == tailY[i]) || (x == playerX && y == playerY)) {
			valid = false;
		}

	}

	if (!valid) {
		pair<int, int> foodLoc;
		foodLoc = make_pair(-100, -100);
		return foodLoc;
	}

	pair<int, int> foodLoc;
	foodLoc = make_pair(x, y);

	return foodLoc;
}
