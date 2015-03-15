#pragma once

class IPlayerController
{
protected:
	double m_turnValue;
public:
	IPlayerController()
		: m_turnValue{}
	{

	}
	// Returns the value the player wants to turn that tick, in between -0.5 & 0.5
	// negative turns left, positive turns right
	virtual double getValue()
	{
		return m_turnValue;
	}

	// Tells the player if he is dead or has won.
	virtual void updateStatus(bool isWinner)
	{

	}
};