#include "vect2d.h"
#include <math.h>


vect2d::vect2d(void)
{
	this->X = 0;
	this->Y = 0;
}

vect2d::vect2d(float x, float y)
{
	this->X = x;
	this->Y = y;
}

void vect2d::setX(float x) {
	this->X = x;
}
void vect2d::setY(float y) {
	this->Y = y;
}

float vect2d::getX() {
	return X;
}

float vect2d::getY() {
	return Y;
}


vect2d::~vect2d() 
{
	
}