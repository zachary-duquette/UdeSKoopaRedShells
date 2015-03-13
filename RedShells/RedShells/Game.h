#pragma once
#include "GameState.h"
#include <vector>

class IPlayerController;

class Game
{
private:
	struct Player
	{
		int mi_playerNumber;
		bool mi_isAlive;
		float mi_angle;
		IPlayerController* mi_playerController;
	};

	static Game* m_singleton;

	static const int MINIMUM_VARIATION_DEGREE;

	GameState m_gameState;

	std::vector<Player> m_players;

	bool m_canPlayersJoin;

	Game();

	int GetRandomStartDirection() const;

public:
	static Game* GetGame();

	GameState& GetGameState();

	void StartGame();

	void Tick();

	bool IsGameFinished() const;

	int GetNumberOfPlayers() const;

	void AddPlayer(IPlayerController* playerController);

	bool CanPlayersJoin() const;
};