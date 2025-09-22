#pragma once

#include "StaticObject.hpp"

#include <SDL2/SDL.h>

class AnimObject : public StaticObject
{
public:
	AnimObject(const char* filename, int widthArg, int heightArg, Vector2Int positionArg, int fallSpeedArg);

	const char* image;
	SDL_Rect rect;
	
	int fallSpeed;
	bool movedSquare;
	int currentStep;
	
	virtual void update(int step);
};