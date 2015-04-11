#include "Game.h"
#include "GameState.h"
#include "GameServer.h"
#include "Viewport.h"
#include <iostream>

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#include <chrono>
#include <vector>
#include <cmath>
#include <thread>
#include "KeyboardController.h"
#include "KeyboardControllerManager.h"

using namespace std;

void WaitForPlayers(int value);
void WaitOnStart(int value);

void Draw()
{
	Viewport::Get()->Draw();
}

void Tick(int value)
{
	Game* game = Game::Get();
	if (!game->IsGameFinished())
	{
		auto begin = chrono::system_clock::now();
		game->Tick();
		glutPostRedisplay();
		auto end = chrono::system_clock::now();
		glutTimerFunc((chrono::milliseconds{ Viewport::INTERVAL } -chrono::duration_cast<chrono::milliseconds>(end - begin)).count(), Tick, 0);
	}
	else
	{
		glutTimerFunc(5000, WaitForPlayers, 0);
	}
}

void WaitForPlayers(int value)
{
	Game::Get()->StartGame();
	glutPostRedisplay();
	glutTimerFunc(3000, WaitOnStart, 0);
}

void WaitOnStart(int value)
{
	glutTimerFunc(Viewport::INTERVAL, Tick, 0);
}

void Keyboard(unsigned char key, int x, int y)
{
	Game* game = Game::Get();
	if (key == '1')
	{
		if (!game->IsGameFull())
		{
			game->AddPlayer(KeyboardControllerManager::Get()->GetController());
		}
		glutPostRedisplay();
	}
	else
	{
		KeyboardControllerManager::Get()->KeyPressed(key);
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	KeyboardControllerManager::Get()->KeyReleased(key);
}

void Resize(int width, int height) {
	// we ignore the params and do:
	glutReshapeWindow(Viewport::WIDTH, Viewport::HEIGHT);
}

int main()
{
	// Needed because our main dont have parms, cause the glutInit take the parms of the main 
	//	Default parms when we have some, { appName = "appName" }
	char *myargv[1];
	int myargc = 1;
	myargv[0] = "RedShells";
	glutInit(&myargc, myargv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(Viewport::WIDTH, Viewport::HEIGHT);
	glutCreateWindow("Curve Fever v3.0"); 
	glutReshapeFunc(Resize);
	
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutTimerFunc(5000, WaitOnStart, 0);
	
	Viewport::Get()->Enable2D(Viewport::WIDTH, Viewport::HEIGHT);
	glColor3f(1.0f, 1.0f, 1.0f);
	GameServer *server = GameServer::Get();
	glutMainLoop();
}
