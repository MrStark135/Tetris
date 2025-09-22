#include "PieceSpawner.hpp"
#include "CoreSystem.hpp"

#include <cmath>
#include <iostream>

int random(int low, int high);

void PieceSpawner::spawnPiece()
{
	char* filename = randomSquareColor();
	std::vector<Vector2Int*>* positions = randomPiece();
	
	objects->push_back(new Piece(positions, filename, SIZE, fallspeed));

	// delete positions;
}

char* PieceSpawner::randomSquareColor()
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

std::vector<Vector2Int*>* PieceSpawner::randomPiece()
{
	auto piece = new std::vector<Vector2Int*>();
	
	int randPiece = random(0, CoreSystem::Instance()->pieceManager->pieces->size());
	
	piece = PieceManager::copyPiece((*CoreSystem::Instance()->pieceManager->pieces)[randPiece]); // pointers, kill me
	int maxX = PieceManager::findMax(piece, 'x');
	
	int randX = random(BOARD_BORDER, BOARD_COLS - BOARD_BORDER - maxX + 1);
	for (int i = 0; i < piece->size(); i++)
	{
		(*piece)[i]->x += randX;
	}
	
	// *piece = (*CoreSystem::Instance()->pieceManager->square1x1);
	// *piece = (*CoreSystem::Instance()->pieceManager->square2x2);
	// *piece = (*CoreSystem::Instance()->pieceManager->square3x3);
	
	// *piece = (*CoreSystem::Instance()->pieceManager->l2x2);
	// *piece = (*CoreSystem::Instance()->pieceManager->l3x2);
	// *piece = (*CoreSystem::Instance()->pieceManager->l4x2);
	// *piece = (*CoreSystem::Instance()->pieceManager->l3x3);
	// *piece = (*CoreSystem::Instance()->pieceManager->l4x4);
	
	// *piece = (*CoreSystem::Instance()->pieceManager->s2x2);
	
	// *piece = (*CoreSystem::Instance()->pieceManager->line2);
	// *piece = (*CoreSystem::Instance()->pieceManager->line3);
	// *piece = (*CoreSystem::Instance()->pieceManager->line4);
	
	// piece->push_back(new Vector2Int(randX, 0));
	// piece->push_back(new Vector2Int(randX + 1, 0));
	// piece->push_back(new Vector2Int(randX + 1, 0 + 1));
	// piece->push_back(new Vector2Int(randX + 1, 0 + 2));
	
	return piece;
}

int random(int low, int high)
{
	return (rand() % (high - low) + low);
}