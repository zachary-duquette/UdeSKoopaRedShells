#include "Game.h"
#include <random>
//#include "IPlayerController.h"

using namespace std;

const int Game::MINIMUM_VARIATION_DEGREE = 2;

int Game::GetRandomStartDirection() const
{
	random_device rd;
	mt19937 prng{ rd() };
	uniform_int_distribution<int> randomDirection{ 0, 360 };
	return randomDirection(prng);
}

GameState& Game::GetGameState()
{
	return m_gameState;
}

void Game::StartGame()
{

}

void Game::Tick()
{
	for (auto playerIT = m_players.begin(); playerIT != m_players.end(); ++playerIT)
	{
		if (playerIT->mi_isAlive)
		{
			//Get angle value from interface
			auto newAngle = playerIT->mi_angle + 1;
			bool angleChanged = abs(newAngle - playerIT->mi_angle) > MINIMUM_VARIATION_DEGREE;
			if (angleChanged)
			{
				playerIT->mi_angle = newAngle;
			}
			playerIT->mi_isAlive = m_gameState.MovePlayer(playerIT->mi_playerNumber, playerIT->mi_angle, angleChanged);
		}
	}
}

bool Game::Finished()
{
	int playersDead = 0;
	for (auto playerIT = m_players.begin(); playerIT != m_players.end(); ++playerIT)
	{
		if (!playerIT->mi_isAlive)
		{
			++playersDead;
		}
	}
	return m_players.size() == playersDead + 1;
}

int Game::GetNumberOfPlayers()
{
	return m_players.size();
}

void Game::AddPlayer()
{
	Player newPlayer{};
	newPlayer.mi_playerNumber = m_gameState.AddPlayer();
	newPlayer.mi_angle = static_cast<float>(GetRandomStartDirection());
	newPlayer.mi_isAlive = true;
	m_players.push_back(newPlayer);
}