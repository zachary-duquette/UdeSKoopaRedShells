#pragma once
#include "IPlayerController.h"

class KeyboardController : public IPlayerController
{
	char m_turnRight, m_turnLeft;
public:
	KeyboardController(char left, char right);
	void KeyPressed(unsigned char key);
	void KeyReleased(unsigned char key);
};