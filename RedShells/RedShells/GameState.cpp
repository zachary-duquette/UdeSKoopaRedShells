#include "GameState.h"
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

const double GameState::SPEED = 0.5;
const int GameState::DISTANCE_FROM_OTHER_PLAYER = 5;
const int GameState::DISTANCE_FROM_BORDER_START = 10;
const int GameState::FIELD_SIZE = 50;

GameState::GameState()
{
	
}

GameState::~GameState()
{
}

//Private Methods -----
GameState::Coordinate GameState::GetRandomStartCoordinate() const
{
	random_device rd;
	mt19937 prng{ rd() };
	uniform_int_distribution<int> randomPosition{ DISTANCE_FROM_BORDER_START, FIELD_SIZE - DISTANCE_FROM_BORDER_START };

	bool validStartLocation = false;
	Coordinate startingLineHead{};
	while (!validStartLocation)
	{
		startingLineHead.mi_x = static_cast<double>(randomPosition(prng));
		startingLineHead.mi_y = static_cast<double>(randomPosition(prng));
		validStartLocation = IsFarFromOtherPlayers(startingLineHead);
	}

	return startingLineHead;
}

int GameState::GetRandomStartDirection() const
{
	random_device rd;
	mt19937 prng{ rd() };
	uniform_int_distribution<int> randomDirection{ 0, 360 };
	return randomDirection(prng);
}

bool GameState::IsFarFromOtherPlayers(GameState::Coordinate newPlayerStart) const
{
	for (auto it = m_players.begin(); it != m_players.end(); ++it)
	{
		if (abs(CalculateDistance(newPlayerStart, it->front())) < DISTANCE_FROM_OTHER_PLAYER)
		{
			return false;
		}
	}
	return true;
}

double GameState::CalculateDistance(Coordinate p1, Coordinate p2) const
{
	return sqrt((p2.mi_x - p1.mi_x)*(p2.mi_x - p1.mi_x) + (p2.mi_y - p1.mi_y)*(p2.mi_y - p1.mi_y));
}

GameState::Coordinate GameState::CalculateNewCoordinate(Coordinate coord, double angle) const
{
	double newX = cos(angle * 3.14159265 / 180) * SPEED;
	double newY = sin(angle * 3.14159265 / 180) * SPEED;
	return Coordinate{ coord.mi_x + newX, coord.mi_y + newY };
}

bool GameState::IsOutOfBounds(Coordinate p) const
{
	return p.mi_x > FIELD_SIZE || p.mi_x < 0 || p.mi_y > FIELD_SIZE || p.mi_y < 0;
}

bool GameState::DoesIntersect(Coordinate p1, Coordinate p2, Coordinate q1, Coordinate q2) const
{
	double s1_x, s1_y, s2_x, s2_y;
	s1_x = p2.mi_x - p1.mi_x;     s1_y = p2.mi_y - p1.mi_y;
	s2_x = q2.mi_x - q1.mi_x;     s2_y = q2.mi_y - q1.mi_y;

	double s, t;
	s = (-s1_y * (p1.mi_x - q1.mi_x) + s1_x * (p1.mi_y - q1.mi_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p1.mi_y - q1.mi_y) - s2_y * (p1.mi_x - q1.mi_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		return true; // Intersection
	}

	return false; // No intersection
}

//Public Methods -----

int GameState::AddPlayer()
{
	PlayerLine playerLine;
	playerLine.emplace_back(GetRandomStartCoordinate());
	m_players.push_back(playerLine);
	return m_players.size();
}

int GameState::GetNumberPlayers() const
{
	return m_players.size();
}

GameState::Coordinate GameState::GetLineHeadForPlayer(int playerNumber) const
{
	return m_players[playerNumber-1].back();
}

void GameState::Print() const
{
	for (unsigned int i = 0; i < m_players.size(); ++i)
	{
		cout << "Player " << i + 1 << " coordinates : " << endl;
		for (unsigned int j = 0; j < m_players[i].size(); ++j)
		{
			cout << "X : " << m_players[i][j].mi_x << " Y : " << m_players[i][j].mi_y << endl;
		}
	}
}

bool GameState::MovePlayer(int playerNumber, double angle)
{
	//Calculate new dot
	auto newCoordinate = CalculateNewCoordinate(m_players[playerNumber - 1].back(), angle);
	//Check if collisions
	if (IsOutOfBounds(newCoordinate))
	{
		return false;
	}
	else
	{
		for (auto playerIT = m_players.begin(); playerIT != m_players.end(); ++playerIT)
		{
			for (auto coordIT = playerIT->begin(); (coordIT + 1) != playerIT->end(); ++coordIT)
			{
				if (DoesIntersect(m_players[playerNumber - 1].back(), newCoordinate, *coordIT, *(coordIT + 1)))
				{
					if ((coordIT + 1) != (m_players[playerNumber - 1].end() - 1))
					{
						return false;
					}
				}
			}
		}
	}
	//Move head
	m_players[playerNumber - 1].push_back(newCoordinate);
	return true;
}

vector<GameState::PlayerLine> GameState::getLines() const
{
	return m_players;
}