#include "PieceManager.hpp"
#include <iostream>

// operations on pieces
void PieceManager::movePiece(std::vector<Vector2Int*>* piece, int xAxis, int yAxis)
{
	for (int i = 0; i < piece->size(); i++)
	{
		(*piece)[i]->x += xAxis;
		(*piece)[i]->y += yAxis;
	}
}
void PieceManager::rotatePiece(std::vector<Vector2Int*>* piece)
{
	int xOff = findMax(piece, 'x') - findSize(piece, 'x');
	int yOff = findMax(piece, 'y') - findSize(piece, 'y');
	
	int size = findSize(piece);
	
	for (int i = 0; i < piece->size(); i++)
	{
		int tmp = (*piece)[i]->x - xOff;
		(*piece)[i]->x = (*piece)[i]->y - yOff + xOff;
		(*piece)[i]->y = size - tmp + yOff - 1;
	}
}
void PieceManager::flipPiece(std::vector<Vector2Int*>* piece, int xAxis, int yAxis)
{
	for (int i = 0; i < piece->size(); i++)
	{
		(*piece)[i]->x *= xAxis;
		(*piece)[i]->y *= yAxis;
	}
}
int PieceManager::findMax(std::vector<Vector2Int*>* piece, char axis)
{
	int maxX = 0;
	int maxY = 0;
	
	for (int i = 0; i < piece->size(); i++)
	{
		if ((*piece)[i]->x > maxX) maxX = (*piece)[i]->x;
		if ((*piece)[i]->y > maxY) maxY = (*piece)[i]->y;
	}
	
	maxX += 1;
	maxY += 1;
	
	if (axis == 'x') return maxX;
	if (axis == 'y') return maxY;
	if (axis == 0) return (maxX > maxY) ? maxX : maxY;
}
int PieceManager::findSize(std::vector<Vector2Int*>* piece, char axis)
{
	sortSquares(piece, 'x');
	int diffX = (*piece)[0]->x - (*piece)[piece->size()-1]->x + 1;
	
	sortSquares(piece, 'y');	
	int diffY = (*piece)[0]->y - (*piece)[piece->size()-1]->y + 1;

	if (axis == 'x') return diffX;
	if (axis == 'y') return diffY;
	if (axis == 0) return (diffX > diffY) ? diffX : diffY;
}
void PieceManager::sortSquares(std::vector<Vector2Int*>* squarePositions, char axis)
{
	bool change = true;
	
	while (true)
	{
		if (change != true) break;
		
		change = false;
		
		for (int i = 0; i < squarePositions->size() - 1/* since I take the next element */; i++)
		{
			Vector2Int* curr = (*squarePositions)[i];
			Vector2Int* next = (*squarePositions)[i + 1];
			
			if (axis == 'x')
			{
				if (curr->x < next->x)
				{
					change = true;
					
					Vector2Int tmp = *curr;
					*curr = (*next);
					*next = tmp;
				}
			}
			else if (axis == 'y')
			{
				if (curr->y < next->y)
				{
					change = true;
					
					Vector2Int tmp = *curr;
					*curr = (*next);
					*next = tmp;
				}
			}
			else return;
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------


// same thing when used for Squares, overloads
void PieceManager::movePiece(std::vector<Square*>* piece, int xAxis, int yAxis)
{
	for (int i = 0; i < piece->size(); i++)
	{
		(*piece)[i]->position.x += xAxis;
		(*piece)[i]->position.y += yAxis;
	}
}
void PieceManager::rotatePiece(std::vector<Square*>* piece)
{
	int xOff = findMax(piece, 'x') - findSize(piece, 'x');
	int yOff = findMax(piece, 'y') - findSize(piece, 'y');
	
	// std::cout << "maxX: " << findMax(piece, 'x') << ", sizeX: " << findSize(piece, 'x') << "\n";
	// std::cout << "maxY: " << findMax(piece, 'y') << ", sizeY: " << findSize(piece, 'y') << "\n";
	
	// std::cout << "---before----\n";
	// for (int i = 0; i < piece->size(); i++)
	// 	std::cout << "elem[" << i << "]=(" << (*piece)[i]->position.x << ", " << (*piece)[i]->position.y << ")\n"; 
	// std::cout << "-------------\n" << findSize(piece) << "\n";
	
	int size = findSize(piece);
	
	for (int i = 0; i < piece->size(); i++)
	{
		// std::cout << "elem(old) = " << (*piece)[i]->position.x - xOff << ", " << (*piece)[i]->position.y - yOff << "\n";
		
		int tmp = (*piece)[i]->position.x - xOff;
		(*piece)[i]->position.x = (*piece)[i]->position.y - yOff + xOff;
		(*piece)[i]->position.y = size - tmp + yOff - 1;
		
		// std::cout << "elem(new) = " << (*piece)[i]->position.x << ", " << (*piece)[i]->position.y << "\n";
	}
}
void PieceManager::flipPiece(std::vector<Square*>* piece, int xAxis, int yAxis)
{
	for (int i = 0; i < piece->size(); i++)
	{
		(*piece)[i]->position.x *= xAxis;
		(*piece)[i]->position.y *= yAxis;
	}
}
int PieceManager::findMax(std::vector<Square*>* piece, char axis)
{
	int maxX = 0;
	int maxY = 0;
	
	for (int i = 0; i < piece->size(); i++)
	{
		if ((*piece)[i]->position.x > maxX) maxX = (*piece)[i]->position.x;
		if ((*piece)[i]->position.y > maxY) maxY = (*piece)[i]->position.y;
	}
	
	maxX += 1;
	maxY += 1;
	
	if (axis == 'x') return maxX;
	if (axis == 'y') return maxY;
	if (axis == 0) return (maxX > maxY) ? maxX : maxY;
}
int PieceManager::findSize(std::vector<Square*>* piece, char axis)
{
	// std::cout << "---before----\n";
	// for (int i = 0; i < piece->size(); i++)
	// 	std::cout << "elem[" << i << "]=(" << (*piece)[i]->position.x << ", " << (*piece)[i]->position.y << ")\n"; 
	// std::cout << "-------------\n";
	sortSquares(piece, 'x');
	// std::cout << "----sortx----\n";
	// for (int i = 0; i < piece->size(); i++)
	// 	std::cout << "elem[" << i << "]=(" << (*piece)[i]->position.x << ", " << (*piece)[i]->position.y << ")\n"; 
	// std::cout << "-------------\n";
	
	int diffX = (*piece)[0]->position.x - (*piece)[piece->size()-1]->position.x + 1;
	
	sortSquares(piece, 'y');
	// std::cout << "-------------\n";
	// for (int i = 0; i < piece->size(); i++)
	// 	std::cout << "elem[" << i << "]=(" << (*piece)[i]->position.x << ", " << (*piece)[i]->position.y << ")\n"; 
	// std::cout << "-------------\n";
	
	int diffY = (*piece)[0]->position.y - (*piece)[piece->size()-1]->position.y + 1;

	if (axis == 'x') return diffX;
	if (axis == 'y') return diffY;
	if (axis == 0) return (diffX > diffY) ? diffX : diffY;
}
void PieceManager::sortSquares(std::vector<Square*>* squarePositions, char axis)
{
	bool change = true;
	
	while (true)
	{
		if (change != true) break;
		
		change = false;
		
		for (int i = 0; i < squarePositions->size() - 1/* since I take the next element */; i++)
		{
			Square* curr = (*squarePositions)[i];
			Square* next = (*squarePositions)[i + 1];
			
			if (axis == 'x')
			{
				if (curr->position.x < next->position.x)
				{
					change = true;
					
					Square tmp = *curr;
					*curr = (*next);
					*next = tmp;
				}
			}
			else if (axis == 'y')
			{
				if (curr->position.y < next->position.y)
				{
					change = true;
					
					Square tmp = *curr;
					*curr = (*next);
					*next = tmp;
				}
			}
			else return;
		}
	}
}

std::vector<Vector2Int*>* PieceManager::copyPiece(std::vector<Vector2Int*>* originalPiece)
{
	auto copyPiece = new std::vector<Vector2Int*>();
	for (int i = originalPiece->size() - 1; i >= 0; i--)
	{
		copyPiece->push_back(new Vector2Int((*originalPiece)[i]->x, (*originalPiece)[i]->y));
	}
	
	return copyPiece;
}

void PieceManager::loadPieces()
{
	pieces = new std::vector<std::vector<Vector2Int*>*>();
	
	std::vector<Vector2Int*>* square1x1 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0)
	});
	pieces->push_back(square1x1);
	std::vector<Vector2Int*>* square2x2 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0),
		new Vector2Int(1, 0),
		new Vector2Int(0, 1),
		new Vector2Int(1, 1)
	});
	pieces->push_back(square2x2);
	// ----- illegal piece -----
	// std::vector<Vector2Int*>* square3x3 = new std::vector<Vector2Int*>
	// ({
	// 	new Vector2Int(0, 0),
	// 	new Vector2Int(1, 0),
	// 	new Vector2Int(2, 0),
	// 	new Vector2Int(0, 1),
	// 	new Vector2Int(1, 1),
	// 	new Vector2Int(2, 1),
	// 	new Vector2Int(0, 2),
	// 	new Vector2Int(1, 2),
	// 	new Vector2Int(2, 2)
	// });
	// pieces->push_back(square3x3);
	
	std::vector<Vector2Int*>* l2x2 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0),
		new Vector2Int(0, 1),
		new Vector2Int(1, 1)
	});
	pieces->push_back(l2x2);
	std::vector<Vector2Int*>* l3x2 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0),
		new Vector2Int(0, 1),
		new Vector2Int(0, 2),
		new Vector2Int(1, 2)
	});
	pieces->push_back(l3x2);
	std::vector<Vector2Int*>* l4x2 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0),
		new Vector2Int(0, 1),
		new Vector2Int(0, 2),
		new Vector2Int(0, 3),
		new Vector2Int(1, 3)
	});
	pieces->push_back(l4x2);
	std::vector<Vector2Int*>* l3x3 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0),
		new Vector2Int(0, 1),
		new Vector2Int(0, 2),
		new Vector2Int(1, 2),
		new Vector2Int(2, 2)
	});
	pieces->push_back(l3x3);
	// std::vector<Vector2Int*>* l4x4 = new std::vector<Vector2Int*>
	// ({
	// 	new Vector2Int(0, 0),
	// 	new Vector2Int(0, 1),
	// 	new Vector2Int(0, 2),
	// 	new Vector2Int(0, 3),
	// 	new Vector2Int(1, 3),
	// 	new Vector2Int(2, 3),
	// 	new Vector2Int(3, 3)
	// });
	// pieces->push_back(l4x4);
	
	std::vector<Vector2Int*>* s2x2 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0),
		new Vector2Int(1, 0),
		new Vector2Int(1, 1),
		new Vector2Int(2, 1)
	});
	pieces->push_back(s2x2);
	
	std::vector<Vector2Int*>* line2 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0),
		new Vector2Int(0, 1)
	});
	pieces->push_back(line2);
	std::vector<Vector2Int*>* line3 = new std::vector<Vector2Int*>
	({
		new Vector2Int(0, 0),
		new Vector2Int(0, 1),
		new Vector2Int(0, 2)
	});
	pieces->push_back(line3);
	// std::vector<Vector2Int*>* line4 = new std::vector<Vector2Int*>
	// ({
	// 	new Vector2Int(0, 0),
	// 	new Vector2Int(0, 1),
	// 	new Vector2Int(0, 2),
	// 	new Vector2Int(0, 3)
	// });
	// pieces->push_back(line4);
}

void PieceManager::deletePieces()
{
	delete square1x1;
	
	delete square2x2;
	delete square3x3;
	
	delete l2x2;
	delete l3x2;
	delete l4x2;
	delete l3x3;
	delete l4x4;
	
	delete s2x2;
	
	delete line2;
	delete line3;
	delete line4;
}