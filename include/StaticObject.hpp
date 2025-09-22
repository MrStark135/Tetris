#pragma once

#include "Vector2Int.hpp"

#include <SDL2/SDL.h>

// only renders an image, doesn't update or do anything
class StaticObject
{
public:
	StaticObject(const char* filename, int widthArg, int heightArg, Vector2Int positionArg);

	const char* image;
	SDL_Rect rect;
	
	virtual void update(int step);
	virtual void render();
};