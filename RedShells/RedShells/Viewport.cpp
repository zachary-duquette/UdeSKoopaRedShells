
#include "Viewport.h"
#include "Game.h"
#include "KeyboardControllerManager.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"

#include <chrono>
#include <vector>

using namespace std;

const int Viewport::WIDTH = 800;
const int Viewport::HEIGHT = 600;
const int Viewport::BOARD_INITIAL_SIZE = 600;
const int Viewport::INTERVAL = 1000 / 30;
Viewport* Viewport::m_singleton = nullptr;


const vector<GLfloat> RED{ 1.0f, 0.0f, 0.0f };
const vector<GLfloat> GREEN{ 0.0f, 1.0f, 0.0f };
const vector<GLfloat> BLUE{ 0.0f, 0.0f, 1.0f };
const vector<GLfloat> VIOLET{ 1.0f, 0.0f, 1.0f };
const vector<GLfloat> YELLOW{ 1.0f, 1.0f, 0.0f };
const vector<GLfloat> TURQUOISE{ 0.0f, 1.0f, 1.0f };

const vector<GLfloat> WHITE{ 1.0f, 1.0f, 1.0f };

const vector<vector<GLfloat>> COLORS{ BLUE, RED, YELLOW, GREEN, VIOLET, TURQUOISE };


Viewport* Viewport::Get()
{
	if (!m_singleton)
		m_singleton = new Viewport();
	return m_singleton;
}

void Viewport::Enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);


	glLineWidth(5);
	glPointSize(8.0);
}

void Viewport::SetPlayerColor(int player)
{
	glColor3f(COLORS[player][0], COLORS[player][1], COLORS[player][2]);
}

void Viewport::DrawLine(vector<GameState::Coordinate> points, int player)
{
	if (!points.empty())
	{
		glColor3f(COLORS[player][0], COLORS[player][1], COLORS[player][2]);

		double x, y;

		x = points[0].mi_x * (m_pixelFieldSzie / GameState::FIELD_SIZE);
		y = points[0].mi_y * (m_pixelFieldSzie / GameState::FIELD_SIZE);

		glBegin(GL_LINE_STRIP);
		for (size_t i = 1; i < points.size(); ++i)
		{
			x = points[i].mi_x * static_cast<float>(m_pixelFieldSzie / static_cast<float>(GameState::FIELD_SIZE));
			y = points[i].mi_y * static_cast<float>(m_pixelFieldSzie / static_cast<float>(GameState::FIELD_SIZE));
			double x_pred = points[i - 1].mi_x * static_cast<float>(m_pixelFieldSzie / static_cast<float>(GameState::FIELD_SIZE));
			double y_pred = points[i - 1].mi_y * static_cast<float>(m_pixelFieldSzie / static_cast<float>(GameState::FIELD_SIZE));

			glVertex2d(x_pred, y_pred);
			glVertex2d(x, y);
		}
		glEnd();

		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
	}
}

void Viewport::DrawField()
{
	glTranslatef(5.0f, 5.0f, 0.0f);
	m_pixelFieldSzie -= 10; // double because of padding left/right (up/down)
	
	Game* game = Game::Get();
	for (size_t i = 0; i < game->GetGameState().getLines().size(); ++i)
	{
		DrawLine(game->GetGameState().getLines()[i], i);
	}
	
}

void Viewport::WriteText(const char* text, int length)
{
	for (int i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}

void Viewport::DrawInfo()
{
	//glRasterPos2i(m_pixelFieldSzie + 10, HEIGHT - 34);
	vector<string> playerList{ "Player 1", "Player 2", "Player 3", "Player 4" };
	string textToWrite{};

	for (int i = 0; i < Game::Get()->GetNumberOfPlayers(); ++i)
	{
		SetPlayerColor(i);

		glRasterPos2i(m_pixelFieldSzie + 10, HEIGHT - (34 * (i + 1)));
		textToWrite = playerList[i];

		WriteText(textToWrite.data(), textToWrite.length());
	}
}

void Viewport::DrawWall()
{
	glColor3f(WHITE[0], WHITE[1], WHITE[2]);
	glTranslatef(10.0f, 10.0f, 0.0f);
	m_pixelFieldSzie -= 20; // double because of padding left/right (up/down)

	glColor3f(WHITE[0], WHITE[1], WHITE[2]);

	auto fieldSize = static_cast<GLfloat>(m_pixelFieldSzie);

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(fieldSize, 0.0f);

	glVertex2f(fieldSize, fieldSize);

	glVertex2f(0.0f, fieldSize);


	glEnd();
}

void Viewport::Draw()
{
	m_pixelFieldSzie = min(HEIGHT, WIDTH);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	DrawWall();
	DrawField();
	DrawInfo();

	glutSwapBuffers();
}