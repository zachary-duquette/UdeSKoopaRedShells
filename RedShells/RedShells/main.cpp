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

	gameState.Print();

	gameState.MovePlayer(1, 0);
	gameState.MovePlayer(2, 90);
	gameState.MovePlayer(3, 180);
	gameState.MovePlayer(4, 270);

	gameState.Print();

	auto end = chrono::system_clock::now();
	cout << "Time spent : " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
}
