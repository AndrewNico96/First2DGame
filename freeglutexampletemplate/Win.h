#pragma once
#include "BackGround.h"
class Win
{
private:
	int screenWidth = 1000, screenHeight = 600;
	vect2d v = vect2d(0.0f, -50.0f);
	BackGround * menu = new BackGround(v, "WinterTileset/BG/WIN.png", 0.0f, 20000.0f, 10000.0f);
public:
	Win();
	void loop();
	~Win();
};

