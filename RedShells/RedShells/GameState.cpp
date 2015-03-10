#include "GameState.h"
#include <iostream>
#include <random>

using namespace std;

// Simplified char to hex printer
// http://stackoverflow.com/questions/673240/how-do-i-print-an-unsigned-char-as-hex-in-c-using-ostream
struct HexCharStruct
{
	unsigned char c;
	HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::hex << static_cast<int>(hs.c));
}

inline HexCharStruct hex(unsigned char _c)
{
	return HexCharStruct(_c);
}

GameState::GameState()
{
	//Set everything as empty
	for (int y = 0; y < FIELD_SIZE; ++y)
	{
		for (int x = 0; x < FIELD_SIZE; ++x)
		{
			m_field[y][x] = EMPTY;
		}
	}
	//Add external walls
	for (int x = 0; x < FIELD_SIZE; ++x)
	{
		m_field[0][x] = WALL;
		m_field[FIELD_SIZE-1][x] = WALL;
	}
	for (int y = 0; y < FIELD_SIZE; ++y)
	{
		m_field[y][0] = WALL;
		m_field[y][FIELD_SIZE-1] = WALL;
	}
}

//Private Methods -----
GameState::LineHead GameState::GetRandomStart()
{
	random_device rd;
	mt19937 prng{ rd() };
	uniform_int_distribution<int> randomPosition{ DISTANCE_FROM_BORDER_START, FIELD_SIZE - DISTANCE_FROM_BORDER_START };
	uniform_int_distribution<int> randomDirection{ 0, NB_DIRECTIONS - 1 };

	bool validStartLocation = false;
	LineHead startingLineHead{};
	while (!validStartLocation)
	{
		startingLineHead.mi_position.mi_x = randomPosition(prng);
		startingLineHead.mi_position.mi_y = randomPosition(prng);
		startingLineHead.mi_direction = static_cast<Direction>(randomDirection(prng));
		validStartLocation = ValidateStartLocation(startingLineHead);
	}

	return startingLineHead;
}

bool GameState::ValidateStartLocation(GameState::LineHead newPlayer)
{
	//Assumes that DISTANCE_FROM_OTHER_PLAYER < DISTANCE_FROM_BORDER_START
	auto minX = newPlayer.mi_position.mi_x - DISTANCE_FROM_OTHER_PLAYER;
	auto minY = newPlayer.mi_position.mi_y - DISTANCE_FROM_OTHER_PLAYER;
	auto maxX = newPlayer.mi_position.mi_x + DISTANCE_FROM_OTHER_PLAYER;
	auto maxY = newPlayer.mi_position.mi_y + DISTANCE_FROM_OTHER_PLAYER;

	for (int y = minY; y < maxY; ++y)
	{
		for (int x = minX; x < maxX; ++x)
		{
			if (m_field[y][x] != EMPTY)
			{
				return false;
			}
		}
	}
	return true;
}

//Public Methods -----

int GameState::AddPlayer()
{
	GameState::LineHead newPlayer = GetRandomStart();
	m_players.push_back(newPlayer);
	m_field[newPlayer.mi_position.mi_y][newPlayer.mi_position.mi_x] = static_cast<FieldValue>(m_players.size());
	return m_players.size();
}

int GameState::GetNumberPlayers()
{
	return m_players.size();
}

GameState::LineHead GameState::GetLineHeadForPlayer(int playerNumber)
{
	return m_players[playerNumber-1];
}

void GameState::PrintField()
{
	cout << "Amount of players : " << m_players.size() << endl;
	cout << "-----------------------------------------" << endl;
	for (int y = 0; y < FIELD_SIZE; ++y)
	{
		cout << "|";
		for (int x = 0; x < FIELD_SIZE; ++x)
		{
			cout << hex(m_field[y][x]);
		}
		cout << "|" << endl;
	}
	cout << "-----------------------------------------" << endl;
}

bool GameState::MovePlayer(int playerNumber, GameState::Direction direction)
{
	auto oldX = m_players[playerNumber-1].mi_position.mi_x;
	auto oldY = m_players[playerNumber-1].mi_position.mi_y;
	auto newX = 0;
	auto newY = 0;
	switch (direction)
	{
	case NORTH:
		newX = oldX;
		newY = oldY - 1;
		break;
	case NORTH_EAST:
		newX = oldX + 1;
		newY = oldY - 1;
		break;
	case EAST:
		newX = oldX + 1;
		newY = oldY;
		break;
	case SOUTH_EAST:
		newX = oldX + 1;
		newY = oldY + 1;
		break;
	case SOUTH:
		newX = oldX;
		newY = oldY + 1;
		break;
	case SOUTH_WEST:
		newX = oldX - 1;
		newY = oldY + 1;
		break;
	case WEST:
		newX = oldX - 1;
		newY = oldY;
		break;
	case NORTH_WEST:
		newX = oldX - 1;
		newY = oldY - 1;
		break;
	default:
		newX = oldX;
		newY = oldY;
		break;
	}

	if (m_field[newY][newX] != EMPTY)
	{
		m_players[playerNumber-1].mi_alive = false;
		return false;
	}
	else
	{
		m_players[playerNumber-1].mi_position.mi_x = newX;
		m_players[playerNumber-1].mi_position.mi_y = newY;
		m_players[playerNumber-1].mi_direction = direction;
		m_field[newY][newX] = static_cast<FieldValue>(playerNumber);
		return true;
	}
}