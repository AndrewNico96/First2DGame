#include "MovingPlatform.h"



MovingPlatform::MovingPlatform()
{
}

MovingPlatform::MovingPlatform(vect2d centre, float length, float height, vect2d origin, char * textureName) : Platform(centre, length, height, Platform::material::MOVING, textureName)
{
	this->origin = origin;
	velocityX = 0.3f;
	this->myTexture = loadPNG("WinterTileset/Object/Crate.png");
}

MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::move() {
	if (abs(abs(centre.getX()) - abs(origin.getX())) > 100)
		velocityX = -velocityX;
}