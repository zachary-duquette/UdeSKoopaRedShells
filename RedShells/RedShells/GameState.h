#pragma once
#include <vector>

class GameState
{
public:
	struct Coordinate
	{
		double mi_x;
		double mi_y;
		Coordinate()
			:mi_x{}, mi_y{}
		{
		}
		Coordinate(double x, double y)
			:mi_x{ x }, mi_y{ y }
		{
		}
	};

	typedef std::vector<Coordinate> Player;

	static const int FIELD_SIZE;

private:
	static const int DISTANCE_FROM_BORDER_START;
	static const int DISTANCE_FROM_OTHER_PLAYER;
	static const double SPEED;

	std::vector<Player> m_players;

	Coordinate GetRandomStartCoordinate() const;

	int GetRandomStartDirection() const;

	bool IsFarFromOtherPlayers(Coordinate newPlayer) const;

	double CalculateDistance(Coordinate p1, Coordinate p2) const;

	Coordinate CalculateNewCoordinate(Coordinate p, double angle) const;

	bool IsOutOfBounds(Coordinate p) const;

	bool DoesIntersect(Coordinate p1, Coordinate p2, Coordinate q1, Coordinate q2) const;

public:
	GameState();
	~GameState();

	//Returns Player Number
	int AddPlayer();

	int GetNumberPlayers() const;

	Coordinate GetLineHeadForPlayer(int playerNumber) const;
	
	// Angle is 0 to 360, 0 is X axis
	bool MovePlayer(int playerNumber, double angle);

	void Print() const;

	std::vector<Player> getLines() const;
};