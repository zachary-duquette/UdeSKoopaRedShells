#include "KeyboardController.h"

KeyboardController::KeyboardController(char left, char right)
	:m_turnRight{ right }, m_turnLeft{ left }
{
}

void KeyboardController::KeyPressed(unsigned char key)
{
	if (key == m_turnRight)
	{
		m_turnValue = -0.5;
	}
	else if (key == m_turnLeft)
	{
		m_turnValue = 0.5;
	}
}

void KeyboardController::KeyReleased(unsigned char key)
{
	if (key == m_turnRight || key == m_turnLeft)
	{
		m_turnValue = 0;
	}
}