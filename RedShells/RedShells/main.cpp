#include "Game.h"
#include "GameState.h"
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

const int WIDTH = 800;
const int HEIGHT = 600;
const int BOARD_INITIAL_SIZE = 600;
const int INTERVAL = 1000 / 30;


const vector<GLfloat> RED{ 1.0f, 0.0f, 0.0f };
const vector<GLfloat> GREEN{ 0.0f, 1.0f, 0.0f };
const vector<GLfloat> BLUE{ 0.0f, 0.0f, 1.0f };
const vector<GLfloat> VIOLET{ 1.0f, 0.0f, 1.0f };
const vector<GLfloat> YELLOW{ 1.0f, 1.0f, 0.0f };
const vector<GLfloat> TURQUOISE{ 0.0f, 1.0f, 1.0f };

const vector<GLfloat> WHITE{ 1.0f, 1.0f, 1.0f };

const vector<vector<GLfloat>> colors{ BLUE, RED, YELLOW, GREEN, VIOLET, TURQUOISE };

int angle = 10;

void DrawLine(vector<GameState::Coordinate> points, int player)
{
	if (!points.empty())
	{
		glColor3f(colors[player][0], colors[player][1], colors[player][2]);

		double x, y;

		x = points[0].mi_x * (BOARD_INITIAL_SIZE / GameState::FIELD_SIZE);
		y = points[0].mi_y * (BOARD_INITIAL_SIZE / GameState::FIELD_SIZE);

		glBegin(GL_LINE_STRIP);
		for (size_t i = 1; i < points.size(); ++i)
		{
			x = points[i].mi_x * static_cast<float>(BOARD_INITIAL_SIZE / static_cast<float>(GameState::FIELD_SIZE));
			y = points[i].mi_y * static_cast<float>(BOARD_INITIAL_SIZE / static_cast<float>(GameState::FIELD_SIZE));
			double x_pred = points[i - 1].mi_x * static_cast<float>(BOARD_INITIAL_SIZE / static_cast<float>(GameState::FIELD_SIZE));
			double y_pred = points[i - 1].mi_y * static_cast<float>(BOARD_INITIAL_SIZE / static_cast<float>(GameState::FIELD_SIZE));
			
			glVertex2d(x_pred, y_pred);
			glVertex2d(x, y);
		}
		glEnd();

		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
	}
}

void DrawWall()
{
	glColor3f(WHITE[0], WHITE[1], WHITE[2]);

	GLfloat width = static_cast<GLfloat>(glutGet(GLUT_WINDOW_WIDTH) - 10);
	GLfloat height = static_cast<GLfloat>(glutGet(GLUT_WINDOW_HEIGHT) - 10);

	GLfloat gameRes = min(width, height);

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(gameRes, 0.0f);

	glVertex2f(gameRes, gameRes);

	glVertex2f(0.0f, gameRes);


	glEnd();

}

void DrawViewport()
{
	Game* game = Game::Get();
	for (size_t i = 0; i < game->GetGameState().getLines().size(); ++i)
	{
		DrawLine(game->GetGameState().getLines()[i], i);
	}
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	float scale = 1 - (BOARD_INITIAL_SIZE - 20) / BOARD_INITIAL_SIZE;

	glTranslatef(10.0f, 10.0f, 0.0f);
	glScalef(scale, scale, 1.0f);

	glLineWidth(5);
	DrawWall();

	glTranslatef(5.0f, 5.0f, 0.0f);

	glPointSize(8.0);
	glLineWidth(5);
	DrawViewport();

	glutSwapBuffers();
}

void Enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
}

void WaitForPlayers(int value);
void WaitOnStart(int value);

void Tick(int value)
{
	Game* game = Game::Get();
	if (!game->IsGameFinished())
	{
		auto begin = chrono::system_clock::now();
		game->Tick();
		glutPostRedisplay();
		auto end = chrono::system_clock::now();
		glutTimerFunc((chrono::milliseconds{ INTERVAL } -chrono::duration_cast<chrono::milliseconds>(end - begin)).count(), Tick, 0);
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
	glutTimerFunc(INTERVAL, Tick, 0);
}

void Keyboard(unsigned char key, int x, int y)
{
	Game* game = Game::Get();
	if (key == '1')
	{
		if (game->GetNumberOfPlayers() < 4)
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


int main()
{
	// Needed because our main dont have parms, cause the glutInit take the parms of the main 
	//	Default parms when we have some, { appName = "appName" }
	char *myargv[1];
	int myargc = 1;
	myargv[0] = "RedShells";
	glutInit(&myargc, myargv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Curve Fever v3.0");

	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutTimerFunc(5000, WaitOnStart, 0);

	Enable2D(WIDTH, HEIGHT);
	glColor3f(1.0f, 1.0f, 1.0f);

	glutMainLoop();
}
