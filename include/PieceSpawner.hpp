#pragma once

#include "Piece.hpp"
#include <vector>

class PieceSpawner
{
public:
	void spawnPiece();
	
	// helpers
	char* randomSquareColor();
	std::vector<Vector2Int*>* randomPiece();
	
	std::vector<Piece*>* objects;
	float fallspeed;
};