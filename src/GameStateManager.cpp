#include "GameStateManager.hpp"
#include "CoreSystem.hpp"
#include "AnimObject.hpp"
#include "Piece.hpp"

#include <iostream>

void GameStateManager::Init()
{
	// setup the gameBoard
	CoreSystem::Instance()->boardCellsTaken.clear();
	for (int i = 0; i < BOARD_ROWS + TOP_PADDING + BOARD_BORDER; i++)
	{
		CoreSystem::Instance()->boardCellsTaken.push_back(std::vector<int>());
		
		// the last rows -> border
		if (i >= BOARD_ROWS + TOP_PADDING)
			for (int j = 0; j < BOARD_COLS + 2 * BOARD_BORDER; j++) // +2 since there are 2 side borders
				CoreSystem::Instance()->boardCellsTaken[i].push_back(2);

		// all the other lines				
		else 
			for (int j = 0; j < BOARD_COLS + 2 * BOARD_BORDER; j++) // +2 since there are 2 side borders
			{
				if (j < BOARD_BORDER || j >= BOARD_COLS + BOARD_BORDER) // the first and the last -> the borders of the gameBoard
					CoreSystem::Instance()->boardCellsTaken[i].push_back(2);
				else
					CoreSystem::Instance()->boardCellsTaken[i].push_back(0);
			}
	}
	
	// PieceSpawner
	CoreSystem::Instance()->pieceSpawner->fallspeed = START_SPEED;
	
	// UIObjects
	CoreSystem::Instance()->uiObjects.push_back(new TextObject(string("0"), FONT_PATH, {225, 225, 225}, "assets/gameBoardSquare.png", SIZE * 2 + 10, SIZE, 10, Vector2Int(SIZE - 10, SIZE)));
	for (int y = 0; y < BOARD_ROWS; y++)
	{
		for(int x = 0; x < BOARD_COLS; x++)
		{
			CoreSystem::Instance()->uiObjects.push_back(new StaticObject("assets/gameBoardSquare.png", SIZE, SIZE, Vector2Int(x * SIZE + BOARD_XPOS, y * SIZE + BOARD_YPOS)));
		}
	}
	
	// Helper
	CoreSystem::Instance()->passedPieces = 0;
	CoreSystem::Instance()->score = 0;
	
	state = PLAYING;
}

void GameStateManager::GameOver()
{
	CoreSystem::Instance()->objects.clear();
	CoreSystem::Instance()->uiObjects.clear();
}


void GameStateManager::resetAnimation()
{
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			std::vector<Vector2Int*>* position = new std::vector<Vector2Int*>();
			position->push_back(new Vector2Int(i, -j));
			AnimObject* object = new AnimObject(randomSquareColor(), SIZE, SIZE, Vector2Int(0, 0), FASTEST_SPEED);
			
			CoreSystem::Instance()->uiObjects.push_back(object);
		}
	}	
}

int GameStateManager::random(int low, int high)
{
	return (rand() % (high - low) + low);
}

char* GameStateManager::randomSquareColor()
{
	int i = random(1, 5);
	
	switch (i)
	{
		case 1: return "assets/redSquare.png";
		case 2:	return "assets/greenSquare.png";
		case 3:	return "assets/blueSquare.png";
		case 4: return "assets/yellowSquare.png";
	}
	
	__throw_bad_function_call();
}