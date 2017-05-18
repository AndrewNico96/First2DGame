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

class level1
{
private:
	int screenWidth = 1000, screenHeight = 600;

	std::vector<tile *> tiles;
	//projectile container
	std::vector<projectile *> projectiles;

	vect2d water = vect2d(0.0f, -990.0f);

	//essential vectors for staring positions of objects
	vect2d player = vect2d(800.0f, 50.0f);

	//platforms/tiles
	vect2d v = vect2d(0.0f, 0.0f);
	vect2d v2 = vect2d(1050.0f, 100.0f);
	vect2d v3 = vect2d(2050.0f, 160.0f);
	vect2d v4 = vect2d(2180.0f, 160.0f);
	vect2d v5 = vect2d(1230.0f, 240.0f);
	vect2d v6 = vect2d(450.0f, 350.0f);
	vect2d v7 = vect2d(260.0f, 400.0f);
	vect2d v8 = vect2d(1000.0f, 300.0f); 	//moving platform
	vect2d v9 = vect2d(660.0f, 300.0f);
	vect2d v10 = vect2d(440.0f, 480.0f);

	//arrow1
	vect2d arr1 = vect2d(1300.0f, 120.0f);
	vect2d arr2 = vect2d(1250.0f, 260.0f);
	vect2d arr3 = vect2d(500.0f, 500.0f);

	//token
	vect2d tok = vect2d(1400.0f, 510.0f);

	vect2d npcCentre = vect2d(1500.0f, 470.0f);
	vect2d npcOrigin = vect2d(1500.0f, 430.0f);

	follower * navi = new follower(v10);
	
	npc * anNpc = new npc(npcCentre, 50, 0.1f, npcOrigin, 30, 30, "character_alpha.png");

	//player
	Player * pl = new Player(player, 100, 10, 20, "character/alienBlue_stand.png");

	Object2D * token = new Object2D(tok, 100, 20.0f, 20.0f, 0.0f, "WinterTileset/Object/Crystal.png");

	//arrows
	Object2D * arrow1 = new Object2D(arr1, 100, 30.0f, 30.0f, 0.0f, "WinterTileset/Object/sign_2.png");
	Object2D * arrow2 = new Object2D(arr2, 100, 30.0f, 30.0f, 0.0f, "WinterTileset/Object/sign_3.png");
	Object2D * arrow3 = new Object2D(arr3, 100, 30.0f, 30.0f, 0.0f, "WinterTileset/Object/sign_2.png");

	BackGround * BG = new BackGround(v,"WinterTileset/BG/BG.png", 0.0f, 10000.0f, 10000.0f);

	BackGround * waterForeGround = new BackGround(water, "WinterTileset/Tiles/17.png", 0.001f, 10000.0f, 1000.0f);

	MovingPlatform * p = new MovingPlatform(v8, 50.0f, 20.0f, v8, "character_alpha.png");

	//Boundbox for collision with non-static objects
	BoundBox b = BoundBox();

public:
	level1();
	~level1();
	void loop();
	Object2D * getToken();
	BackGround * getBG();
	Player * getPlayer();
	//passes mouse values through to attack function of player
	void shoot(float x, float y);
};

