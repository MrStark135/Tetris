#pragma once

#include "StaticObject.hpp"
#include <string>
#include <SDL2/SDL_ttf.h>

class TextObject : public StaticObject
{
public:
	TextObject(std::string textArg, std::string fontPath, SDL_Color color, const char* filename, int widthArg, int heightArg, int padding, Vector2Int positionArg);
	~TextObject();
	
	virtual void update();
	virtual void render();
	
	std::string text;
	SDL_Rect textRect;
	TTF_Font* font;
	int fontSize;
	SDL_Color color;
};