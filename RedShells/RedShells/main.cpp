#include "GameState.h"
#include <iostream>
#include <chrono>

using namespace std;


int main()
{
	auto begin = chrono::system_clock::now();
	GameState gameState{};

	gameState.AddPlayer();
	gameState.AddPlayer();
	gameState.AddPlayer();
	gameState.AddPlayer();

	gameState.PrintField();

	gameState.MovePlayer(1, GameState::EAST);
	gameState.MovePlayer(2, GameState::NORTH_EAST);
	gameState.MovePlayer(3, GameState::SOUTH);
	gameState.MovePlayer(4, GameState::SOUTH);

	gameState.PrintField();

	auto end = chrono::system_clock::now();
	cout << "Time spent : " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
}
