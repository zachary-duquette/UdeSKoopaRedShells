#pragma once
#include "GameState.h"
#include <vector>

//class IPlayerController;

class Game
{
	struct Player
	{
		int mi_playerNumber;
		bool mi_isAlive;
		float mi_angle;
		//IPlayerController* mi_playerController;
	};

private:
	int GetRandomStartDirection() const;

public:
	GameState& GetGameState();

	void StartGame();
	void Tick();
	bool Finished();
	int GetNumberOfPlayers();
	void AddPlayer();

private:
	static const int MINIMUM_VARIATION_DEGREE;
	GameState m_gameState;
	std::vector<Player> m_players;
};