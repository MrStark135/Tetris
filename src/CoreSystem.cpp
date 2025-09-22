#include <iostream>

#include "CoreSystem.hpp"

#include <cmath>
#include <math.h>

// input related
#define MOUSE_MOVE 0
#define MOUSE_LEFT 1
#define MOUSE_MIDDLE 2
#define MOUSE_RIGHT 3
#define ESCAPE_KEY 41

// UI objects
#define UI_OBJECT_IDX_SCORE 0

CoreSystem* CoreSystem::instance;

int random(int low, int high);

void CoreSystem::Update()
{
	// std::cout << "enter update\n";
	
	// regulate game speed
	frameSize = float(std::clock() - lastFrameTime) / CLOCKS_PER_SEC;
	lastFrameTime = std::clock();
	frameSize = frameSize > 0.009f ? frameSize : 0.009f;
	// std::cout << frameSize << std::endl;
	
	// counts steps, gameSpeed
	if (currentStep >= STEPSIZE)
	{
		currentStep = 0;
		step++;
	}
	currentStep += frameSize;
	frame++;
	
	// UPDATE OBJECTS
	// uiObjects
	for (int i = 0; i < uiObjects.size(); i++)
		uiObjects[i]->update(step);
	// gameObjects
	for (int i = 0; i < objects.size(); i++)
		objects[i]->update(step);
	
	// if (lastStep != step && input->mouseMiddleButton)
	// {
	// 	for (int i = 0; i < boardCellsTaken.size(); i++)
	// 	{
	// 		for (int j = 0; j < boardCellsTaken[i].size(); j++)
	// 			cout << boardCellsTaken[i][j] << " ";
	// 		cout << "\n";
	// 	}
		
	// 	lastStep = step;
	// }
	
	// Piece spawninig and speed regulating
	bool noMovingPiece = true;
	for (int i = 0; i < objects.size(); i++)
	{
		if (!objects[i]->pieceLanded)
		{
			noMovingPiece = false;
		}
	}
	if (noMovingPiece)
	{
		pieceSpawner->spawnPiece();
		score += SLOWEST_SPEED - pieceSpawner->fallspeed;
		(dynamic_cast<TextObject*>(uiObjects[UI_OBJECT_IDX_SCORE]))->text = to_string(score);
		passedPieces++;
		if (passedPieces >= INCREMENT_INTERVAL_PIECES)
		{
			cout << "passedPieces: " << passedPieces << "\nspeed: " << pieceSpawner->fallspeed << "\n";
			passedPieces = 0;
			if (pieceSpawner->fallspeed - INCREMENT_SPEED < FASTEST_SPEED) { pieceSpawner->fallspeed = FASTEST_SPEED; }
			else { pieceSpawner->fallspeed -= INCREMENT_SPEED; }
		}
	}
	
	// check for gameOver
	for (int i = 0; i < boardCellsTaken[0].size(); i++)
	{
		if (i < BOARD_BORDER || i >= BOARD_COLS + BOARD_BORDER) // the first and the last -> the borders of the gameBoard
			continue;
		if (boardCellsTaken[TOP_PADDING][i] == 2) gameStateManager->state = GAME_OVER;
	}
	if (gameStateManager->state == GAME_OVER)
	{
		gameStateManager->GameOver();
		gameStateManager->resetAnimation();
		gameStateManager->Init();
	}
	
	// std::cout << "exit update\n";
}

void CoreSystem::Render()
{
	// std::cout << "enter render\n";
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	// uiObjects
	for (int i = 0; i < uiObjects.size(); i++)
		uiObjects[i]->render();	
	// gameObjects
	for (int i = 0; i < objects.size(); i++)
		objects[i]->render();
	
	SDL_RenderPresent(renderer);
	
	// std::cout << "exit render\n";
}

void CoreSystem::Init()
{
	// Initialize SDL video
	if (SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
		return;
	}
	// Create window
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN /* | SDL_VIDEO_DRIVER_WAYLAND  *//* | SDL_WINDOW_FULLSCREEN_DESKTOP */);
	if (window == NULL)
	{
		std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
		return;
	}
	// Get window surface
	renderer = SDL_CreateRenderer(window, -1, 0);
	// just a debug message
	std::cout << "SDL initialized successfully\n";
	
	// SDL_TTF init, necessary to init library
	TTF_Init();
	
	// initialize all modules
	input = new Input();
	input->keysDown = SDL_GetKeyboardState(0);
	textureManager = new TextureManager();
	textureManager->renderer = renderer;	
	
	gameStateManager = new GameStateManager();
	gameStateManager->state = INIT;
	
	// initialize game objects, add to the scene immediately
	objects = std::vector<Piece*>();
	
	// std::vector<Vector2Int*>* l3x2 = new std::vector<Vector2Int*>
	// ({
	// 	new Vector2Int(0 + 5, 0 + 7),
	// 	new Vector2Int(0 + 5, 1 + 7),
	// 	new Vector2Int(0 + 5, 2 + 7),
	// 	new Vector2Int(1 + 5, 2 + 7)
	// });
	// vector<Vector2Int*>* positionsObj2 = new vector<Vector2Int*>();
	// positionsObj2->push_back(new Vector2Int(5, 5));
	// positionsObj2->push_back(new Vector2Int(6, 5));
	// positionsObj2->push_back(new Vector2Int(5, 6));
	// positionsObj2->push_back(new Vector2Int(6, 6));
	// // add initial objects to the scene
	// objects.push_back(new Piece(l3x2, "assets/redSquare.png", SIZE, 1));
	// objects.push_back(new Piece(positionsObj2, "assets/greenSquare.png", SIZE, 3));
	
	pieceManager = new PieceManager();
	pieceManager->loadPieces();
	
	pieceSpawner = new PieceSpawner();
	pieceSpawner->objects = &objects;
	
	// initalize UIObjects
	uiObjects = std::vector<StaticObject*>();
	
	// timing vars setup
	lastFrameTime = std::clock();
	step = 0;
	frame = 0;
	
	// helper vars setup
	running = true;
	lastStep = -1;
	srand(time(0));
	score = 0;
	
	gameStateManager->Init();
	gameStateManager->resetAnimation();
	
	std::cout << "CoreSystem initialized successfully\n";
}

void CoreSystem::CheckEvents()
{
	std::cout << "enter check events\n";
	
	SDL_Event event1;
	
	if (SDL_PollEvent(&event1) != 0)
	{
		// std::cout << "event " << input->event << std::endl;
		
		// std::cout << "event\n";
		
		switch (event1.type)
		{
			case SDL_QUIT: running = false; break;
			case SDL_MOUSEMOTION:
			{
				input->mousePosX = event1.motion.x;
				input->mousePosY = event1.motion.y;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				int buttonID = int(event1.button.button);
				
				if (buttonID == 1) { input->mouseLeftButton = true; break; }
				else if (buttonID == 2) { input->mouseMiddleButton = true; break; }
				else if (buttonID == 3) input->mouseRightButton = true;
				
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				int buttonID = int(event1.button.button);
				
				if (buttonID == 1) { input->mouseLeftButton = false; break; }
				else if (buttonID == 2) { input->mouseMiddleButton = false; break; }
				else if (buttonID == 3) input->mouseRightButton = false;
				
				break;
			}
			case SDL_KEYDOWN:
			{
				input->keysDown = SDL_GetKeyboardState(0);
				
				// Quit if Escape pressed
				if (input->isKeyDown(ESCAPE_KEY))
					running = false;
				// cout << event1.key.keysym.scancode << endl;
				
				break;
			}
			default: break;
		}
		
		// std::cout << "end-event\n";
	}
	
	// std::cout << "exiting checkEvents\n";
}


void CoreSystem::Quit()
{
	
	// delete forcesRegistery;
	// delete draggableRegistry;
	std::cout << "CoreSystem Quit\n";
	
	// delete all objects with for loop: TODO
	pieceManager->deletePieces();
	
	delete pieceManager;
	delete pieceSpawner;
	delete textureManager;
	delete input;
	
	// Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Quit SDL subsystems
	SDL_Quit();
	std::cout << "SDL Quit\n";
}