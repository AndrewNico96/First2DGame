#pragma once
#include "OBject2D.h"

class projectile : public Object2D
{
private:

	int damage;
	vect2d target;
	float speed;

public:
	projectile();
	
	projectile(vect2d c, int heal, vect2d target, float r, int d, float speed, char * textureName);

	int getDamage();

	void setVelocity();

	void posUpdate();

};

