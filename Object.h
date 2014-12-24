#pragma once
#include <string>

using namespace std;

struct position{
	float x;
	float y;
};

struct caracteristics {
	float width;
	float height;
};

class Object
{
public:
	Object(float x, float y, float w, float h);
	~Object();

	position* getPosition();
	void setPosition(float x, float y);
	void setCaracteristics(float w, float h);

protected: 
	string m_name;
	position m_pos;
	caracteristics m_carac;
	int spriteNumber;
};

