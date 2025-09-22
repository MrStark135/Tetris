#include "Square.hpp"
#include "CoreSystem.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

Square::Square(const char* filename, int sizeArg, Vector2Int positionArg, int fallSpeedArg)
	: position(positionArg), image(filename), fallSpeed(fallSpeedArg), currentStep(0), movedSquare(false)
{		
	// rendering rect
	rect = SDL_Rect();
	rect.x = position.x * SIZE;
	rect.y = position.y * SIZE;
	rect.w = sizeArg;
	rect.h = sizeArg;
	
	CoreSystem::Instance()->boardCellsTaken[position.y][position.x] = 1;
	
	CoreSystem::Instance()->textureManager->LoadPNG(filename);
}

void Square::update(int step)
{
	if (currentStep != step)
		movedSquare = false;
	
	if (movedSquare) return;
	
	if (step % fallSpeed == 0)
	{
		CoreSystem::Instance()->boardCellsTaken[position.y][position.x] = 0;
		position.y++;
		CoreSystem::Instance()->boardCellsTaken[position.y][position.x] = 1;
		
		movedSquare = true;
		currentStep = step;
	}
}

int Square::checkCollision(std::string direction)
{
	if (direction == "down") return CoreSystem::Instance()->boardCellsTaken[position.y + 1][position.x];
	if (direction == "right") return CoreSystem::Instance()->boardCellsTaken[position.y][position.x + 1];
	if (direction == "left") return CoreSystem::Instance()->boardCellsTaken[position.y][position.x - 1];
	else __throw_invalid_argument;
}

void Square::landSquare()
{
	CoreSystem::Instance()->boardCellsTaken[position.y][position.x] = 2;
}

void Square::render()
{
	rect.x = (position.x - BOARD_BORDER) * SIZE;
	rect.y = (position.y - TOP_PADDING) * SIZE;
	
	if (position.y < TOP_PADDING) return;
	
	CoreSystem::Instance()->textureManager->Draw(image, rect.x + BOARD_XPOS, rect.y + BOARD_YPOS, rect.w, rect.h);
}