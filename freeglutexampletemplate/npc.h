#pragma once
#include "Player.h"
class npc : public Player
{
private:
	vect2d origin;
	GLuint snowManRight = loadPNG("WinterTileset/Object/SnowMan.png");
	GLuint snowManLeft = loadPNG("WinterTileset/Object/SnowMan2.png");
public:
	npc();

	npc(vect2d c, int heal, float velocityX, vect2d origin, float l, float h, char * textureName);
	
	~npc();

	void ai(vect2d player);

	void move();

	void chase(vect2d player);

	void aim(vect2d target);
};

