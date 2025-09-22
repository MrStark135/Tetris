#pragma once

/**  ----- UNIVERSAL SETUP, GLOBAL VARS etc. -----

// Screen, gameBoard etc. dimensions
// for now, not resizable, remains as TODO
/*
	xxxx xxxx xxxx xxxx xxxx xxxx = 20
	xxxx BBBB BBBB BBBB BBBB xxxx
	xxxx BBBB BBBB BBBB BBBB xxxx
			*	*	*	*
	xxxx BBBB BBBB BBBB BBBB xxxx
	xxxx BBBB BBBB BBBB BBBB xxxx
	xxxx xxxx xxxx xxxx xxxx xxxx
	= 20
	
	boardRows = 18
	boardCols = 12
	sideMargins = 4
	verticalMargins = 1
**/

// "measure unit"
#define SIZE 48 // size of the squares (Pixels), which defines all objects in the scene basically - BORDER INCLUDED
#define BORDER 4 // all squares have borders (Pixels), depends on the sprite, set =0 if the is no border

#define BOARD_ROWS 16
#define BOARD_COLS 14
#define TOP_PADDING 4 // how many cells on top are added, which aren't visible, if 0, pieces will spawn in the board immediately 
#define BOARD_BORDER 1 // cells that are border of the board

// window size
const int SCREEN_WIDTH = 22 * SIZE;
const int SCREEN_HEIGHT = 18 * SIZE;

// game board dimensions and position
const int BOARD_XPOS = 4 * SIZE;
const int BOARD_YPOS = 1 * SIZE;
const int BOARD_HEIGHT = BOARD_ROWS * SIZE;
const int BOARD_WIDTH = BOARD_COLS * SIZE;

#define STEPSIZE 0.1f // related to the speed of pieces (float)
#define FASTEST_SPEED 5 // fastest speed of a piece (int)
#define SLOWEST_SPEED 15 // slowest speed of a piece (int)
#define START_SPEED 18 // initial_speed speed of a piece (int)
#define INCREMENT_SPEED 1 // amount for which the speed increases every INCREMENT_INTERVAL_PIECES pieces (int)
#define INCREMENT_INTERVAL_PIECES 2 // after how many pieces, the speed gets incremented (int)