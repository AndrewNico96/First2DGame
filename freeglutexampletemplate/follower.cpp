#include "follower.h"



follower::follower()
{
}

follower::follower(vect2d centre)
{
	this->centre = centre;
	this->length = 15.0f;
	this->height = 15.0f;
	this->radius = 0.0f;
	this->myTexture = loadPNG("character/hud_p3Alt.png");
	this->health = 100;
}

void follower::follow(vect2d player) {
	//Normalise vector
	float distanceX; 
	float distanceY = player.getY() - centre.getY() + 40;
	
	//keep follower behing player
	if (centre.getX() <= player.getX() + 15) 
		distanceX = player.getX() - 40 - centre.getX();
	else
		distanceX = player.getX() + 40 - centre.getX();
	
	float hyp = sqrt(distanceX*distanceX + distanceY*distanceY);

	//adjust velocities
	velocityX = (distanceX / hyp) * speed;
	velocityY = (distanceY / hyp) * speed;
}

//overrides position update so follower can fly
void follower::posUpdate() {
	grounded = true;
	centre.setX(centre.getX() + (velocityX * deltaT)/5);
	centre.setY(centre.getY() + (velocityY * deltaT)/5);
}

follower::~follower()
{
}
