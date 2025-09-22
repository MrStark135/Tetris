#include "TextureManager.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
using namespace std;

bool TextureManager::LoadPNG(const char* filename)
{
	// return type of the loading function
	SDL_Surface* tempSurface;
	
	// texture and it's dimensions are stored separately
	SDL_Texture* texture;
	SDL_Rect* rect = new SDL_Rect();
	
	if (CheckLoadedPNG(filename)) return true;
	
	tempSurface = IMG_Load(filename);
	rect->h = int(tempSurface->h);
	rect->w = int(tempSurface->w);
	
	if (renderer == nullptr)
	{
		cout << "Renderer not initialized\n";
		return false;
	}
	if (tempSurface == nullptr)
	{
		cout << "Image '" << filename << "' not loaded\n";
		return false;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		
		if (texture != nullptr)
		{
			// teture
			textures[filename] = texture;

			// dimensions
			rect->h = tempSurface->h;
			rect->w = tempSurface->w;
			textureDims[filename] = rect;
			
			cout << "Image '" << filename << "' loaded successfully\n";
		}
	}
	return true;
}
bool TextureManager::CheckLoadedPNG(const char* filename)
{
	map<string, SDL_Texture*>::iterator it = textures.find(filename);
	
	if (it->first == filename) return true;
	else return false;
}
void TextureManager::RemovePNG(const char* filename)
{
	textures.erase(filename);
	textureDims.erase(filename);
}

void TextureManager::Draw(string id, int x, int y, int width, int height)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = textureDims[id]->w;
	srcRect.h = textureDims[id]->h;
	
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopy(renderer, textures[id], &srcRect, &destRect);
}
void TextureManager::DrawRotated(string id, int x, int y, int width, int height, float angle)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = textureDims[id]->w;
	srcRect.h = textureDims[id]->h;
	
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopyEx(renderer, textures[id], &srcRect, &destRect, angle, 0, SDL_FLIP_NONE);
}
void TextureManager::DrawFrame(string id, int currentRow, int currentFrame, int srcw, int srch, int destx, int desty, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = (currentFrame - 1) * srcw;
	srcRect.y = (currentRow - 1) * srch;
	srcRect.w = srcw;
	srcRect.h = srch;

	destRect.x = destx;
	destRect.y = desty;
	destRect.w = srcw;
	destRect.h = srch;

	SDL_RenderCopyEx(renderer, textures[id], &srcRect, &destRect, 0, 0, flip);
}
void TextureManager::DrawTile(string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame)
{
	SDL_Rect srcRect, destRect;
	srcRect.x = margin + (width + spacing) * currentFrame;
	srcRect.y = margin + (height + spacing) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(renderer, textures[id], &srcRect, &destRect);
}