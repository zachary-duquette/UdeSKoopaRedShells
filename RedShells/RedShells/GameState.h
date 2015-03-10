#include <vector>

class GameState
{
public:
	struct Position
	{
		int mi_x;
		int mi_y;
		Position(int x, int y)
			:mi_x{ x }, mi_y{ y }
		{
		}
	};

	enum Direction
	{
		NORTH,
		NORTH_EAST,
		EAST,
		SOUTH_EAST,
		SOUTH,
		SOUTH_WEST,
		WEST,
		NORTH_WEST,
		NB_DIRECTIONS
	};

	struct LineHead
	{
		Position mi_position;
		Direction mi_direction;
		bool mi_alive;

		LineHead()
			: mi_position{0,0}
		{

		}

		LineHead(int x, int y, Direction direction)
			: mi_position{ x, y }, mi_direction{ direction }, mi_alive{ true }
		{
		}
		LineHead(Position position, Direction direction)
			: mi_position{ position }, mi_direction{ direction }, mi_alive{ true }
		{
		}
	};

	enum FieldValue : char
	{
		EMPTY,
		PLAYER_ONE,
		PLAYER_TWO,
		PLAYER_THREE,
		PLAYER_FOUR,
		WALL
	};

	static const int FIELD_SIZE = 50;
	//static const int FIELD_SIZE = 256;
private:
	static const int DISTANCE_FROM_BORDER_START = 10;
	//static const int DISTANCE_FROM_BORDER_START = 50;
	static const int DISTANCE_FROM_OTHER_PLAYER = 5;

	char m_field[FIELD_SIZE][FIELD_SIZE];
	std::vector<LineHead> m_players;

	LineHead GetRandomStart();
	bool ValidateStartLocation(LineHead newPlayer);

public:
	GameState();

	//Returns Player Number
	int AddPlayer();

	int GetNumberPlayers();

	LineHead GetLineHeadForPlayer(int playerNumber);
	
	// Return false if collision
	bool MovePlayer(int playerNumber, Direction direction);

	void PrintField();
};