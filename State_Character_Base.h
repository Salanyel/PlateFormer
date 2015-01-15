#pragma once

enum CHARACTER_STATES
{
	STAND,
	RUN,
	JUMP,
	FLY,
	LAND
};

class State_Character_Base
{
public:
	State_Character_Base();
	~State_Character_Base();

	virtual bool changeStateAvailable(CHARACTER_STATES newState) = 0;
	virtual bool initState() = 0;
	virtual bool clearState() = 0;
	virtual void operate() = 0;
};