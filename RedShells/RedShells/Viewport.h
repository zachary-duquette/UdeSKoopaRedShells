#pragma once

#include "GameState.h"


class Viewport
{
public:
	static const int WIDTH;
	static const int HEIGHT;
	static const int BOARD_INITIAL_SIZE;
	static const int INTERVAL;


private:
	static Viewport* m_singleton;
	int m_pixelFieldSzie = HEIGHT;

	void DrawLine(std::vector<GameState::Coordinate>, int);
	void DrawWall();
	void DrawField();
	void DrawInfo();

public:
	static Viewport* Get();

	void Draw();
	void Enable2D(int, int);
};