#pragma once

#include<SDL.h>
#include<SDL_ttf.h>
#include<vector>
#include<string>
#include<iostream>
#include<ctime>

using namespace std;



class Game
{
private:

	int tailLength;
	vector<int> tailX;
	vector<int> tailY;

	int wscale;
	int hscale;

	int x;
	int y;
	int prevX;
	int prevY;

	bool up;
	bool down;
	bool right;
	bool left;

	bool redo;

	pair<int, int> foodLoc;

	SDL_Window* _window;

	float timeX;
	float newTime;
	float delta;

	int speedT;

public :
	Game();
	~Game();
	SDL_Event evnt;
	SDL_Renderer* _renderer;

	SDL_Rect player;
	SDL_Rect food;


	bool inputThisFrame;

	bool isGameRunning();
	void initSystem();

	void processInput();
	void UpdateGame();
	bool checkCollision();
	pair<int, int> getFoodSpawn(vector<int> tailX, vector<int> tailY, int playerX, int playerY, int wscale, int hscale, int tailLength);

};

