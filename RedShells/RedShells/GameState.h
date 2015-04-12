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
		bool operator==(const Coordinate& other)
		{
			return mi_x == other.mi_x && mi_y == other.mi_y;
		}
	};

	typedef std::vector<Coordinate> PlayerLine;

	static const int FIELD_SIZE;

private:
	static const int DISTANCE_FROM_BORDER_START;
	static const int DISTANCE_FROM_OTHER_PLAYER;
	static const double SPEED;

	std::vector<PlayerLine> m_players;

	Coordinate GetRandomStartCoordinate() const;

	bool IsFarFromOtherPlayers(Coordinate newPlayer) const;

	double CalculateDistance(Coordinate p1, Coordinate p2) const;

	Coordinate CalculateNewCoordinate(Coordinate p, double angle) const;

	bool IsOutOfBounds(Coordinate p) const;

	bool DoesIntersect(Coordinate p1, Coordinate p2, Coordinate q1, Coordinate q2) const;

public:

	//Returns Player Number
	int AddPlayer();
	
	// Angle is 0 to 360, 0 is X axis
	bool MovePlayer(int playerNumber, double angle, bool angleChangedFromLastUpdate);

	void Reset();

	void Print() const;

	std::vector<PlayerLine> getLines() const;
};