
class IPlayerController
{
public:
	// Returns the value the player wants to turn that tick, in between -0.5 & 0.5
	// negative turns left, positive turns right
	virtual double getValue() = 0;

	// Tells the player if he is dead or has won.
	virtual void updateStatus(bool isWinner) = 0;
};