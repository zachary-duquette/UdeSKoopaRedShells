#pragma once
#include "IPlayerController.h"

class CellphoneController : public IPlayerController
{	
public:
	CellphoneController();
	
	void UpdateValue(float newValue);
};