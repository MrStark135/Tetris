#pragma once

#include "Square.hpp"

#include <vector>

class Piece
{
public:
	Piece(std::vector<Vector2Int*>* squarePositions, const char* filename, int sizeArg, int fallspeedArg);
	~Piece() { delete piece; };

	virtual void update(int step);
	virtual void render();
	
	// helpers
	bool checkCollisionPiece(std::string direction);
	
	// objects are composed of multiple squares
	std::vector<Square*>* piece;
	
	bool pieceLanded;
};