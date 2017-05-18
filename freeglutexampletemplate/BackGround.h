#pragma once
#include "Object2D.h"
/**
 * inherits functions of Object2D
 * Overrides draw funtion to allow for contant
 * tiling of background
 */
class BackGround : public Object2D
{
public:
	BackGround();
	BackGround(vect2d centre, char * textureName, float scroller, float length, float height);
	float scroller;
	float X = 0;
	//overrides object collision function for repeating texture of background
	void draw();
	~BackGround();
};

