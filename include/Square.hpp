#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Vector2.hpp"
#include "Vector2Int.hpp"

class Square
{
public:
	Square(const char* filename, int sizeArg, Vector2Int positionArg, int fallSpeedArg);
	
	// check for collision efore update is applied
	int checkCollision(std::string direction);
	void landSquare();
	
	virtual void update(int step);
	virtual void render();

	// properties
	Vector2Int position; // position on the game board, not actual Pixel value for the screen
	
	// helper vars
	int fallSpeed;
	bool movedSquare;
	int currentStep;
	
	// rendering
	const char* image;
	SDL_Rect rect;
};