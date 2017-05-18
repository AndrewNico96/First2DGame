#include "npc.h"



npc::npc(){}

npc::npc(vect2d c, int heal, float velocityX, vect2d origin, float l, float h, char * textureName) : Player(c, heal, /*vY, vX,*/ l, h, textureName)
{
	this->origin = origin;
	this->velocityX = abs(velocityX);
	//this->myTexture = loadPNG("WinterTileset/Object/SnowMan2.png");
}


npc::~npc(){}

void npc::ai(vect2d player)
{
	//check player distance
	if (abs(player.getX() - centre.getX()) < 300 &&
		abs(player.getY() - centre.getY()) < 300 &&
		player.getY() > centre.getY() - height / 2) {
		chase(player);
	}
	else
		move();


}

void npc::move() {
	if (abs(abs(centre.getX()) - abs(origin.getX())) > 50) {
		velocityX = -velocityX;
		animationSwitcher++;
	}
	if (animationSwitcher % 2 == 0) {
		myTexture = snowManRight;
	}
	else
		myTexture = snowManLeft;
}

void npc::chase(vect2d player) {
	if (player.getX() < centre.getX()) {
		velocityX = -0.75f;
		myTexture = snowManLeft;
	}
	else if (player.getX() > centre.getX()) {
		velocityX = 0.75f;
		myTexture = snowManRight;
	}
	else
		velocityX = 0;
}


void npc::aim(vect2d target)
{
	
}
