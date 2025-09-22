#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <map>
using namespace std;

class TextureManager
{
public:
	// To add a texture in the map, or to remove from it. The map holds ALL loaded textures by their corresponding IDs
	bool LoadPNG(const char* filename);
	void RemovePNG(const char* filename);
	bool CheckLoadedPNG(const char* filename);

	// different functions to handle drawing to the screen
	void Draw(string id, int x, int y, int width, int height);
	void DrawRotated(string id, int x, int y, int width, int height, float angle);
	void DrawFrame(string id, int currentRow, int currentFrame, int srcw, int srch, int destx, int desty, SDL_RendererFlip flip);
	void DrawTile(string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);
	
	// renderer
	SDL_Renderer* renderer;
	
private:
	// to hold ALL loaded, can be accessed by the corresponding ID, for each texture specified when loaded
	map<string, SDL_Texture*> textures;
	map<string, SDL_Rect*> textureDims;
};

