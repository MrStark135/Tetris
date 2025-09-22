#pragma once

// what the textureManager does with the textures (images), the pieceManager does with the pieces

#include "Vector2Int.hpp"
#include "Square.hpp"
#include <vector>

class PieceManager
{
public:
	void loadPieces();
	void deletePieces();
	
	static void movePiece(std::vector<Vector2Int*>* piece, int xAxis, int yAxis);
	static void rotatePiece(std::vector<Vector2Int*>* piece);
	static void flipPiece(std::vector<Vector2Int*>* piece, int xAxis, int yAxis); /** xAxis and yAxis - set to 1 or -1, -1 means rotate */
	static int findMax(std::vector<Vector2Int*>* piece, char axis = 0);
	static int findSize(std::vector<Vector2Int*>* piece, char axis = 0);
	static std::vector<Vector2Int*>* copyPiece(std::vector<Vector2Int*>* originalPiece);
	static void sortSquares(std::vector<Vector2Int*>* squarePositions, char axis = 'y'); 
	
	// overloads with Square*
	static void movePiece(std::vector<Square*>* piece, int xAxis, int yAxis);
	static void rotatePiece(std::vector<Square*>* piece);
	static void flipPiece(std::vector<Square*>* piece, int xAxis, int yAxis);
	static int findMax(std::vector<Square*>* piece, char axis = 0);
	static int findSize(std::vector<Square*>* piece, char axis = 0);
	static void sortSquares(std::vector<Square*>* squarePositions, char axis = 'y'); 
	
	std::vector<Vector2Int*>* square1x1;
	std::vector<Vector2Int*>* square2x2;
	std::vector<Vector2Int*>* square3x3;
	
	std::vector<Vector2Int*>* l2x2;
	std::vector<Vector2Int*>* l3x2;
	std::vector<Vector2Int*>* l4x2;
	std::vector<Vector2Int*>* l3x3;
	std::vector<Vector2Int*>* l4x4;
	
	std::vector<Vector2Int*>* s2x2;
	
	std::vector<Vector2Int*>* line2;
	std::vector<Vector2Int*>* line3;
	std::vector<Vector2Int*>* line4;
	
	std::vector<std::vector<Vector2Int*>*>* pieces;
};

// EXPLANATION
/**
 * square2x2 =
 * 				- - - -
 * 				- B B -
 * 				- B B -
 * 				- - - -
 * square3x3 =
 * 				B B B -
 * 				B B B -
 * 				B B B -
 * 				- - - -
 * l2x2 =
 * 				- - - -
 * 				- B - -
 * 				- B B -
 * 				- - - -
 * l3x2 =
 * 				- B - -
 * 				- B - -
 * 				- B B -
 */
