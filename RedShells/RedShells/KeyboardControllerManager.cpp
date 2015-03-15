#include "KeyboardControllerManager.h"

KeyboardControllerManager* KeyboardControllerManager::m_singleton = nullptr;
const char KeyboardControllerManager::PLAYER_ONE_LEFT	= 'z';
const char KeyboardControllerManager::PLAYER_ONE_RIGHT	= 'x';
const char KeyboardControllerManager::PLAYER_TWO_LEFT	= 'n';
const char KeyboardControllerManager::PLAYER_TWO_RIGHT	= 'm';
const char KeyboardControllerManager::PLAYER_THREE_LEFT = 'q';
const char KeyboardControllerManager::PLAYER_THREE_RIGHT= 'w';
const char KeyboardControllerManager::PLAYER_FOUR_LEFT	= 'o';
const char KeyboardControllerManager::PLAYER_FOUR_RIGHT = 'p';

KeyboardControllerManager::KeyboardControllerManager()
{
	m_controllers.reserve(4);
}

KeyboardControllerManager* KeyboardControllerManager::Get()
{
	if (!m_singleton)
		m_singleton = new KeyboardControllerManager();
	return m_singleton;
}

KeyboardController* KeyboardControllerManager::GetController()
{
	switch (m_controllers.size())
	{
	case 0:
		m_controllers.emplace_back(PLAYER_ONE_LEFT, PLAYER_ONE_RIGHT);
		break;
	case 1:
		m_controllers.emplace_back(PLAYER_TWO_LEFT, PLAYER_TWO_RIGHT);
		break;
	case 2:
		m_controllers.emplace_back(PLAYER_THREE_LEFT, PLAYER_THREE_RIGHT);
		break;
	case 3:
		m_controllers.emplace_back(PLAYER_FOUR_LEFT, PLAYER_FOUR_RIGHT);
		break;
	}
	return &(m_controllers[m_controllers.size()-1]);
}

void KeyboardControllerManager::KeyPressed(unsigned char key)
{
	for (auto controllerIT = m_controllers.begin(); controllerIT != m_controllers.end(); ++controllerIT)
	{
		controllerIT->KeyPressed(key);
	}
}

void KeyboardControllerManager::KeyReleased(unsigned char key)
{
	for (auto controllerIT = m_controllers.begin(); controllerIT != m_controllers.end(); ++controllerIT)
	{
		controllerIT->KeyReleased(key);
	}
}