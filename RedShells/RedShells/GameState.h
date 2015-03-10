#include <vector>

class GameState
{
private:
	struct Position
	{
		int mi_x;
		int mi_y;
		Position(int x, int y)
			:mi_x{ x }, mi_y{ y }
		{
		}
	};

	struct LineHead
	{
		Position mi_position;
		char mi_direction;

		LineHead(int x, int y, char direction)
			: mi_position{ x, y }, mi_direction{ direction }
		{
		}
	};

	static const int FIELD_SIZE = 50;
	static const int DISTANCE_FROM_BORDER_START = 10;
	//static const int FIELD_SIZE = 256;
	//static const int DISTANCE_FROM_BORDER_START = 50;

	static const LineHead PLAYER_ONE_START; //Top Left
	static const LineHead PLAYER_TWO_START; // Top Right
	static const LineHead PLAYER_THREE_START; //Bottom Left
	static const LineHead PLAYER_FOUR_START; //Bottom Right

	static const char EMPTY = 0X00;
	static const char PLAYER_ONE = 0x01;
	static const char PLAYER_TWO = 0x02;
	static const char PLAYER_THREE = 0x03;
	static const char PLAYER_FOUR = 0x04;

	static const char NORTH = 0x00;
	static const char NORTH_EAST = 0x01;
	static const char EAST = 0x02;
	static const char SOUTH_EAST = 0x03;
	static const char SOUTH = 0x04;
	static const char SOUTH_WEST = 0x05;
	static const char WEST = 0x06;
	static const char NORTH_WEST = 0x07;

	char m_field[FIELD_SIZE][FIELD_SIZE];
	std::vector<LineHead> m_players;

	LineHead GetPlayerStartFromNumber(int number);

public:
	GameState();
	int AddPlayer();

	void Reset();

	void PrintField();
};