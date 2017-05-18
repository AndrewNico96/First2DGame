#include "Platform.h"
#pragma once

class MovingPlatform : public Platform
{

private:
	
	vect2d origin;

public:
	MovingPlatform();

	MovingPlatform(vect2d centre, float length, float height, vect2d origin, char * textureName);

	~MovingPlatform();
	
	//controls movement of the platform
	void move();
};

