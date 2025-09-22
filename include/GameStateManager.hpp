#pragma once

enum GameState
{
	INIT,
	PLAYING,
	GAME_OVER
};

class GameStateManager
{
public:
	void Init();
	void GameOver();
	
	void resetAnimation();
	
	// helpers
	int random(int low, int high);
	char* randomSquareColor();
	
	GameState state;
};