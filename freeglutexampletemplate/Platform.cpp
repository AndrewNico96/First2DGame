#include "Platform.h"
#include <math.h>
#include "GL\freeglut.h"
#include <stdio.h>
#include <iostream>

Platform::Platform() {

}

Platform::Platform(vect2d c, float l, float h, material m, char * textureName) : Object2D(c, health, l, h, 0.0f, textureName)
{
	this->mat = m;
	setStartingHealth();
}

Platform::material Platform::getMat()
{
	return mat;
}

void Platform::groundCheck()
{	
	grounded = true;
}

void Platform::setStartingHealth()
{
	if (mat == ICE) {
		this->health = 20;
	}
	if (mat == SNOW) {
		this->health = 50;
	}
	if (mat == DIRT) {
		this->health = 100;
	}
	if (mat == MOVING) {
		this->health = 250;
	}
}

//overrides position update to keep platform in air
void Platform::posUpdate() {
	grounded = true;
	centre.setX(centre.getX() + (velocityX * deltaT)/5);
}
