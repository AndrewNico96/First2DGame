#pragma once
#include "Image_Loading\glew.h"
#include "GL\freeglut.h"
#include <math.h>
#include "platform.h"
#include "Player.h"
#include "projectile.h"
#include "BoundBox.h"
#include "tile.h"
#include "npc.h"
#include "MovingPlatform.h"
#include "BackGround.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "follower.h"

class level2
{
private:
	int screenWidth = 1000, screenHeight = 600;
	float inc = 0;
	std::vector<tile *> tiles;
	//projectile container
	std::vector<projectile *> projectiles;

	vect2d water = vect2d(0.0f, -990.0f);

	//essential vectors for staring positions of objects
	vect2d player = vect2d(800.0f, 50.0f);

	//platforms/tiles
	vect2d v = vect2d(0.0f, 0.0f);
	vect2d v2 = vect2d(500.0f, 90.0f);
	vect2d v3 = vect2d(750.0f, 180.0f);
	vect2d v4 = vect2d(700.0f, 270.0f);
	vect2d v5 = vect2d(400.0f, 360.0f);
	vect2d v6 = vect2d(700.0f, 450.0f);
	vect2d v7 = vect2d(710.0f, 540.0f);
	vect2d v9 = vect2d(710.0f, 630.0f);
	vect2d v10 = vect2d(440.0f, 710.0f);	//navi (follower) centre

	//token
	vect2d tok = vect2d(460.0f, 740.0f);

	follower * navi = new follower(v10);

	//player
	Player * pl = new Player(player, 100, 10, 20, "character/alienBlue_stand.png");

	Object2D * token = new Object2D(tok, 100, 20.0f, 20.0f, 0.0f, "WinterTileset/Object/Crystal.png");
	BackGround * BG = new BackGround(v, "WinterTileset/BG/BG.png", 0.0f, 10000.0f, 10000.0f);

	BackGround * waterForeGround = new BackGround(water, "WinterTileset/Tiles/17.png", 0.001f, 10000.0f, 1000.0f);

	//Boundbox for collision with non-static objects
	BoundBox b = BoundBox();

public:
	level2();
	~level2();
	void loop();
	Object2D * getToken();
	BackGround * getBG();
	Player * getPlayer();
	//passes mouse values through to attack function of player
	void shoot(float x, float y);
};

