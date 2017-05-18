#include "BoundBox.h"
#include "Player.h"
#include <typeinfo>
#include <iostream>




BoundBox::BoundBox(){}

BoundBox::~BoundBox()
{
	
}

void BoundBox::projectileHit(projectile * a, Object2D * b)
{
	//distance culling
	//check if object or projectile are destroyed (health = 0)
	if (abs(a->getCentre().getX() - b->getCentre().getX()) < 50 &&
		abs(a->getCentre().getY() - b->getCentre().getY()) < 50 &&
		a->getHealth() > 0 && b->getHealth() > 0) {
		float distanceX = a->getCentre().getX() - b->getCentre().getX();
		float distanceY = a->getCentre().getY() - b->getCentre().getY();
		float hypotenuseSquared = b->getLength() *b->getLength() + b->getHeight() * b->getHeight();
		float distanceSquared = distanceX * distanceX + distanceY * distanceY;
		//generic bounding cirle collision check
		if (distanceSquared < hypotenuseSquared + a->getRadius() * a->getRadius()) {
			//damage object
			b->setHealth(b->getHealth() - a->getDamage());
			//kill projectile
			a->setHealth(0);
		}
	}
	
}




void BoundBox::platformCollision(Platform * a, Object2D * b)
{
	//distance culling is done on a per object basis in level
	//check if already colliding or if object is destroyed (health = 0)
	if (!a->getCollision() && !b->getCollision() && a->getHealth() > 0 && b->getHealth() > 0) {
		//bounding box collision check for next frame
		if (a->getCentre().getX() - a->getLength() + a->getVelocityX() < b->getCentre().getX() + b->getLength() + b->getVelocityX() &&
			a->getCentre().getX() + a->getLength() + a->getVelocityX()> b->getCentre().getX() - b->getLength() + b->getVelocityX() &&
			a->getCentre().getY() - a->getHeight() + a->getVelocityY()< b->getCentre().getY() + b->getHeight() + b->getVelocityY() &&
			a->getHeight() + a->getCentre().getY() + a->getVelocityY()> b->getCentre().getY() - b->getHeight() + b->getVelocityY())
		{
			a->setCollision(true);
			b->setCollision(true);
			//A collides below
			b->SetMaterialCollidingWith((Object2D::collidingWith)a->getMat());
			if (a->getCentre().getY() - a->getHeight() +1 >= b->getCentre().getY() + b->getHeight() -1) {
				a->setIsCollidingBelow(true);
				b->setIsCollidingAbove(true);
			}
			//A colliides above
			if (a->getCentre().getY() + a->getHeight() -2< b->getCentre().getY() - b->getHeight() +2) {
				b->setIsCollidingBelow(true);
				a->setIsCollidingAbove(true);
				b->SetMaterialCollidingWith((Object2D::collidingWith)a->getMat());
				b->setInertia(a->getVelocityX());
			}
			//A collides on left
			if (a->getCentre().getX() < b->getCentre().getX() - b->getLength()) {
				a->setIsCollidingLeft(true);
				b->setIsCollidingRight(true);
			}
			//A collides on right 
			if (a->getCentre().getX() > b->getCentre().getX() + b->getLength()) {
				a->setIsCollidingRight(true);
				b->setIsCollidingRight(true);
			}
		}
		else {
			a->setCollision(false);
			b->setCollision(false);
			a->setIsCollidingBelow(false);
			b->setIsCollidingBelow(false);
			a->setIsCollidingAbove(false);
			b->setIsCollidingAbove(false);
			a->setIsCollidingLeft(false);
			b->setIsCollidingLeft(false);
			b->setIsCollidingRight(false);
			a->setIsCollidingRight(false);
		}
	}
}

bool BoundBox::genericCollision(Object2D * a, Object2D * b)
{
	//distance culling
	if (abs(a->getCentre().getX() - b->getCentre().getX()) < 50 &&
		abs(a->getCentre().getY() - b->getCentre().getY()) < 50) {
		//bounding box collision check for current frame
		if (a->getCentre().getX() - a->getLength() < b->getCentre().getX() + b->getLength() &&
			a->getCentre().getX() + a->getLength() > b->getCentre().getX() - b->getLength() &&
			a->getCentre().getY() - a->getHeight() < b->getCentre().getY() + b->getHeight() &&
			a->getHeight() + a->getCentre().getY() > b->getCentre().getY() - b->getHeight())
		{
			a->setCollision(true);
			b->setCollision(true);
			return true;
		}
	}
	else {
		a->setCollision(false);
		b->setCollision(false);
		return false;
	}

}


