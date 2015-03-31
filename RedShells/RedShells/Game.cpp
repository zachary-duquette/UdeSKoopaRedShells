#include "Game.h"
#include <random>
#include "IPlayerController.h"

using namespace std;

Game* Game::m_singleton = nullptr;
const int Game::MINIMUM_VARIATION_DEGREE = 1;

Game::Game()
{

}

Game* Game::Get()
{
	if (!m_singleton)
		m_singleton = new Game();
	return m_singleton;
}

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
	m_canPlayersJoin = false;
	m_gameState.Reset();
	for (auto playerIT = m_players.begin(); playerIT != m_players.end(); ++playerIT)
	{
		playerIT->mi_playerNumber = m_gameState.AddPlayer();
		playerIT->mi_angle = static_cast<float>(GetRandomStartDirection());
		playerIT->mi_isAlive = true;
		m_gameState.MovePlayer(playerIT->mi_playerNumber, playerIT->mi_angle, true);
	}
}

void Game::Tick()
{
	for (auto playerIT = m_players.begin(); playerIT != m_players.end(); ++playerIT)
	{
		if (playerIT->mi_isAlive)
		{
			//Get angle value from interface
			double newAngle = playerIT->mi_angle + (-10 * playerIT->mi_playerController->getValue());
			bool angleChanged = abs(newAngle - playerIT->mi_angle) > MINIMUM_VARIATION_DEGREE;
			if (angleChanged)
			{
				playerIT->mi_angle = newAngle;
			}
			playerIT->mi_isAlive = m_gameState.MovePlayer(playerIT->mi_playerNumber, playerIT->mi_angle, angleChanged);
		}
	}
}

bool Game::IsGameFinished() const
{
	int playersDead = 0;
	for (auto player : m_players)
	{
		if (!player.mi_isAlive)
		{
			++playersDead;
		}
	}
	return (playersDead + 1) >= m_players.size();
}

bool Game::IsGameFull() const
{
	return m_players.size() == MAX_NUM_PLAYERS;
}

int Game::AddPlayer(IPlayerController* playerController)
{
	Player newPlayer{};
	newPlayer.mi_playerNumber = m_gameState.AddPlayer();
	newPlayer.mi_angle = static_cast<float>(GetRandomStartDirection());
	newPlayer.mi_isAlive = true;
	newPlayer.mi_playerController = playerController;
	m_players.push_back(newPlayer);
	m_gameState.MovePlayer(newPlayer.mi_playerNumber, newPlayer.mi_angle, true);
	return newPlayer.mi_playerNumber;
}

bool Game::CanPlayersJoin() const
{
	return m_canPlayersJoin;
}