#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <ctime>

#include "../assets/settings.hpp"

#include "Piece.hpp"
#include "StaticObject.hpp"
#include "Input.hpp"
#include "TextureManager.hpp"
#include "PieceSpawner.hpp"
#include "PieceManager.hpp"
#include "TextObject.hpp"
#include "GameStateManager.hpp"

// the central class of the game, singleton design
class CoreSystem
{
public:
	// OBJECTS
	std::vector<Piece*> objects;
	std::vector<StaticObject*> uiObjects;
	
	// the cells of the board
	std::vector<std::vector<int>> boardCellsTaken;
	
	// MODULES
	Input* input;
	TextureManager* textureManager;
	PieceSpawner* pieceSpawner;
	PieceManager* pieceManager;
	GameStateManager* gameStateManager;
	
	// time related
	float frameSize;
	std::clock_t lastFrameTime;
	
	long long int frame; // how many frames, refreshes since ran
	long long int step; // how many steps since ran
	float currentStep; // sum of frames, until currentStep == STEPSIZE, then it resets
	
	// helper vars
	bool running; // determines if the game should quit
	int lastStep;
	int passedPieces;
	int score;
	
	void Init(); // initialiyes all necessary SDL subsystems
	void Quit(); // quit all SDL subsystems and destroy window

	void Update(); // run all update functions for all the objects
	void Render(); // render everything
	void CheckEvents(); // check for events and run corresponding functions

	// singleton code
	static CoreSystem* Instance()
	{
		if (instance == nullptr)
		{
			instance = new CoreSystem();
		}
		return instance;
	}
	
private:

	// RENDER RELATED
	// The window we'll be rendering to
	SDL_Window* window;
	// The surface contained by the window
	SDL_Renderer* renderer;
	
	// singleton code
	static CoreSystem* instance;
	CoreSystem() {}
};