#include "AnimObject.hpp"
#include "CoreSystem.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

AnimObject::AnimObject(const char* filename, int widthArg, int heightArg, Vector2Int positionArg, int fallSpeedArg)
	: StaticObject(filename, widthArg, heightArg, positionArg), fallSpeed(fallSpeedArg), movedSquare(false) {}

void AnimObject::update(int step)
{
	if (currentStep != step)
		movedSquare = false;
	
	if (movedSquare) return;
	
	if (step % fallSpeed == 0)
	{
		rect.y++;
		
		movedSquare = true;
		currentStep = step;
	}
}