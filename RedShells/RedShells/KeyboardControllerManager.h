#pragma once
#include "KeyboardController.h"
#include <vector>

class KeyboardControllerManager
{
private:
	static const char PLAYER_ONE_LEFT;
	static const char PLAYER_ONE_RIGHT;

	static const char PLAYER_TWO_LEFT;
	static const char PLAYER_TWO_RIGHT;

	static const char PLAYER_THREE_LEFT;
	static const char PLAYER_THREE_RIGHT;

	static const char PLAYER_FOUR_LEFT;
	static const char PLAYER_FOUR_RIGHT;

	static KeyboardControllerManager* m_singleton;

	std::vector<KeyboardController> m_controllers;

	KeyboardControllerManager();

public:
	static KeyboardControllerManager* Get();

	KeyboardController* GetController();

	void KeyPressed(unsigned char key);

	void KeyReleased(unsigned char key);
};