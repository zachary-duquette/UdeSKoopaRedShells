#include "IPlayerController.h"

class KeyboardController : public IPlayerController
{
public:
	KeyboardController(int keyboardPlayerNumber);
	void KeyPressed(unsigned char key);
	void KeyReleased(unsigned char key);
};