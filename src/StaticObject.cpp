#include "StaticObject.hpp"
#include "CoreSystem.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

StaticObject::StaticObject(const char* filename, int widthArg, int heightArg, Vector2Int positionArg)
	: image(filename)
{
	// rendering rect
	rect = SDL_Rect();
	rect.x = positionArg.x;
	rect.y = positionArg.y;
	rect.w = widthArg;
	rect.h = heightArg;
	
	CoreSystem::Instance()->textureManager->LoadPNG(filename);
}

void StaticObject::update(int step)
{
	// doesn't update at all 
}

void StaticObject::render()
{
	CoreSystem::Instance()->textureManager->Draw(image, rect.x, rect.y, rect.w, rect.h);
}