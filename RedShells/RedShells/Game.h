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
		double mi_angle;
		IPlayerController* mi_playerController;
	};

	enum{MAX_NUM_PLAYERS = 4};

	static Game* m_singleton;

	static const int MINIMUM_VARIATION_DEGREE;

	GameState m_gameState;

	std::vector<Player> m_players;

	bool m_canPlayersJoin;

	Game();

	int GetRandomStartDirection() const;

public:
	static Game* Get();

	GameState& GetGameState();

	void StartGame();

	void Tick();

	bool IsGameFinished() const;

	bool IsGameFull() const;

	int AddPlayer(IPlayerController* playerController);

	bool CanPlayersJoin() const;

	void SetPlayersCanJoin(bool canJoin);

	int GetNumberOfPlayers() const;
};