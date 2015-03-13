#include "KeyboardController.h"

KeyboardController::KeyboardController(int keyboardPlayer)
{

}

void KeyboardController::KeyPressed(unsigned char key)
{
	if (key == 'z')
		m_turnValue = 0.5;
	if (key == 'x')
		m_turnValue = -0.5;
}

void KeyboardController::KeyReleased(unsigned char key)
{
	if (key == 'z' || key == 'x')
		m_turnValue = 0;
}