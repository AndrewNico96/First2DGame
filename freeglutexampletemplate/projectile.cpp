#include "projectile.h"
#include <math.h>
#include <iostream>
#include <stdio.h>


projectile::projectile()
{

}

projectile::projectile(vect2d centre, int heal, vect2d target, float r, int d, float speed, char * textureName) : Object2D(centre, heal, 0.0f, 0.0f, r, textureName)
{
	this->damage = d;
	this->target = target;
	this->speed = speed;
	setVelocity();

}

int projectile::getDamage()
{
	return damage;
}

void projectile::setVelocity(){
	//Normalise vector
	float distanceX = target.getX() - centre.getX();
	float distanceY = target.getY() - centre.getY();
	float hyp = sqrt(distanceX*distanceX + distanceY*distanceY);
	
	//adjust velocities
	velocityX = (distanceX / hyp) * speed;
	velocityY = (distanceY / hyp) * speed;
}


void projectile::posUpdate() {
	centre.setX(centre.getX() + (velocityX * deltaT)/5);
	centre.setY(centre.getY() + (velocityY * deltaT)/5);

	groundCheck();
	
	//heavy projectile is affected by gravity
	if (!grounded) {
		velocityY -= gravity;
	}
	groundCheck();
}