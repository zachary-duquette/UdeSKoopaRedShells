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

private:
	GameState m_gameState;
};