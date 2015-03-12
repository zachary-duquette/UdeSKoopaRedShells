#pragma once
#include "GameState.h"

class Game
{
public:
	Game();
	~Game();

	void StartGame();
	void Tick();
	bool Finished();
	int GetNumberOfPlayers();
	int AddPlayer();

private:
	GameState m_gameState;
};