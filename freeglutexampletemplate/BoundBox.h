#pragma once
#include "vect2d.h"
#include "Object2D.h"
#include "projectile.h"
#include "Platform.h"
/**
 * Handles collision detection by drawing a theoretical
 * Axis-Aligned Bounding Box around objects
 * Also handles projectile collision using bounding-cirle 
 * method.
 */

class BoundBox
{
private:

	vect2d centre;
	float length;
	float height;


public:

	BoundBox();

	~BoundBox();

	//checks collision between a projectile and a generic object. 
	//Then calculates the damage dealt to the object and destroys
	//the projectile.
	void projectileHit(projectile * a, Object2D * b);

	//collision check and reaction for platform and object collision
	//determines orientation of collision
	void platformCollision(Platform * a, Object2D * b);

	//generic collision check. returns true if collision is detected.
	//sets objects individual collision values to true.
	bool genericCollision(Object2D * a, Object2D * b);


};

