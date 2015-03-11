#include "GameState.h"
#include "Game.h"
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;


int main()
{
	//Game game{};
	//while (true)
	//{
	//	auto begin = chrono::system_clock::now();
	//	game.Tick();
	//	if (game.Finished())
	//	{
	//		break;
	//	}
	//	auto end = chrono::system_clock::now();
	//	std::this_thread::sleep_for(chrono::milliseconds{ 33 } - chrono::duration_cast<chrono::milliseconds>(end - begin));
	//}



	auto begin = chrono::system_clock::now();
	GameState gameState{};

	gameState.AddPlayer();
	gameState.AddPlayer();
	gameState.AddPlayer();
	gameState.AddPlayer();

	cout << "Player 1 x: " << gameState.GetLineHeadForPlayer(1).mi_position.mi_x << " y: " << gameState.GetLineHeadForPlayer(1).mi_position.mi_y << endl;
	cout << "Player 2 x: " << gameState.GetLineHeadForPlayer(2).mi_position.mi_x << " y: " << gameState.GetLineHeadForPlayer(2).mi_position.mi_y << endl;
	cout << "Player 3 x: " << gameState.GetLineHeadForPlayer(3).mi_position.mi_x << " y: " << gameState.GetLineHeadForPlayer(3).mi_position.mi_y << endl;
	cout << "Player 4 x: " << gameState.GetLineHeadForPlayer(4).mi_position.mi_x << " y: " << gameState.GetLineHeadForPlayer(4).mi_position.mi_y << endl;

	gameState.PrintField();

	gameState.MovePlayer(1, GameState::EAST);
	gameState.MovePlayer(2, GameState::NORTH_EAST);
	gameState.MovePlayer(3, GameState::SOUTH);
	gameState.MovePlayer(4, GameState::SOUTH);

	gameState.PrintField();

	auto end = chrono::system_clock::now();
	cout << "Time spent : " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
}
