#include "GameState.h"
#include <iostream>

using namespace std;

const GameState::LineHead GameState::PLAYER_ONE_START = GameState::LineHead{ GameState::DISTANCE_FROM_BORDER_START, GameState::DISTANCE_FROM_BORDER_START, GameState::SOUTH_EAST }; //Top Left
const GameState::LineHead GameState::PLAYER_TWO_START = GameState::LineHead{ GameState::FIELD_SIZE - GameState::DISTANCE_FROM_BORDER_START, GameState::DISTANCE_FROM_BORDER_START, GameState::SOUTH_WEST }; //Top Right
const GameState::LineHead GameState::PLAYER_THREE_START = GameState::LineHead{ GameState::DISTANCE_FROM_BORDER_START, GameState::FIELD_SIZE - GameState::DISTANCE_FROM_BORDER_START, GameState::NORTH_EAST }; //Bottom Left
const GameState::LineHead GameState::PLAYER_FOUR_START = GameState::LineHead{ GameState::FIELD_SIZE - GameState::DISTANCE_FROM_BORDER_START, GameState::FIELD_SIZE - GameState::DISTANCE_FROM_BORDER_START, GameState::NORTH_WEST }; //Bottom Right

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


// Game State methods
GameState::GameState()
{
	for (int y = 0; y < FIELD_SIZE; ++y)
	{
		for (int x = 0; x < FIELD_SIZE; ++x)
		{
			m_field[y][x] = EMPTY;
		}
	}
}

GameState::LineHead GameState::GetPlayerStartFromNumber(int number)
{
	switch (number)
	{
	case 1:
		return PLAYER_ONE_START;
	case 2:
		return PLAYER_TWO_START;
	case 3:
		return PLAYER_THREE_START;
	case 4:
		return PLAYER_FOUR_START;
	}
	return LineHead{0,0,NORTH};
}

//Returns player number
int GameState::AddPlayer()
{
	return 0;
}

void GameState::Reset()
{

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