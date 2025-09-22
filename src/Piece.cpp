#include "Piece.hpp"
#include "CoreSystem.hpp"

#include <iostream>

Piece::Piece(std::vector<Vector2Int*>* squarePositions, const char* filename, int sizeArg, int fallspeedArg)
	: pieceLanded(false)
{
	PieceManager::sortSquares(squarePositions);
	// sorts the squares of the piece, very important for the order of update
	// so that the squares update in order, no 2 squares in the same cell at once
	
	piece = new std::vector<Square*>();
	
	for (auto iter = squarePositions->begin(); iter != squarePositions->end(); iter++)
		piece->push_back(new Square(filename, sizeArg, *(*iter), fallspeedArg));
	
	// for (auto iter = piece->begin(); iter != piece->end(); iter++)
	// 	cout << "piece = " << (*iter)->position.x << " " << (*iter)->position.y << "\n";
	
	delete squarePositions;
}

void Piece::update(int step)
{
	if (pieceLanded) return;
	
	// moving to sides
	if (CoreSystem::Instance()->input->isKeyDown(ARROW_RIGHT) && CoreSystem::Instance()->frame % 40 == 0 && !checkCollisionPiece("right"))
		PieceManager::movePiece(piece, 1, 0);
	if (CoreSystem::Instance()->input->isKeyDown(ARROW_LEFT) && CoreSystem::Instance()->frame % 40 == 0 && !checkCollisionPiece("left"))
		PieceManager::movePiece(piece, -1, 0);
		
	if (CoreSystem::Instance()->input->isKeyDown(SDL_SCANCODE_R) && CoreSystem::Instance()->frame % 40 == 0)
	{
		PieceManager::rotatePiece(piece);
	}
	
	// land the piece
	if (checkCollisionPiece("down"))
	{
		pieceLanded = true;
		for (auto iter = piece->begin(); iter != piece->end(); iter++)
			(*iter)->landSquare();
		return;
	}
	
	// update the squares
	for (auto iter = piece->begin(); iter != piece->end(); iter++)
	{
		(*iter)->update(step);
	}
}

void Piece::render()
{
	for (auto iter = piece->begin(); iter != piece->end(); iter++)
		(*iter)->render();
}

bool Piece::checkCollisionPiece(std::string direction)
{
	bool collisionDetected = false;
	for (auto iter = piece->begin(); iter != piece->end(); iter++)
	{
		if ((*iter)->checkCollision(direction) == 2) collisionDetected = true;
	}
	
	return collisionDetected;
}