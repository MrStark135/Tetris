#include "TextObject.hpp"
#include "CoreSystem.hpp"
#include <iostream>

#define LETTER_RATIO 0.7f

TextObject::TextObject(std::string textArg, std::string fontPath, SDL_Color colorArg, const char* filename, int widthArg, int heightArg, int padding, Vector2Int positionArg)
	: text(textArg), color(colorArg), StaticObject(filename, widthArg, heightArg, positionArg)
{
	fontSize = rect.h - padding * 2;
	
	font = TTF_OpenFont(fontPath.c_str(), fontSize * 3);
	if (font == NULL) std::cout << "Font \"" << fontPath << "\" not loaded\n";
	else std::cout << "Font \"" << fontPath << "\" loaded successfully\n";
	
	textRect = rect;
	
	textRect.x += padding;
	textRect.y += padding;
	textRect.w -= 2 * padding;
	textRect.h -= 2 * padding;
}

void TextObject::update()
{
	
	textRect.w = text.size() * fontSize * LETTER_RATIO;
}

void TextObject::render()
{
	StaticObject::render();
	
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(CoreSystem::Instance()->textureManager->renderer, textSurface);
	
	SDL_RenderCopy(CoreSystem::Instance()->textureManager->renderer, textTexture, NULL, &textRect);
	
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

TextObject::~TextObject()
{
	TTF_CloseFont(font);
}