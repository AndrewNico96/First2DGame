#pragma once
#include "Image_Loading\glew.h"
#include "vect2d.h"
#include "Image_Loading\nvImage.h"
#include "GL\freeglut.h"
#include "globals.h"


class Object2D
{

public:
	
	enum collidingWith{ DIRT, SNOW, ICE, MOVING };

protected:

	float inertia;	//Stores velocity of contacted objects
	GLuint myTexture = 0;
	char * textureName;
	collidingWith materialCollidingWith; //stores the material in contact 
	const float gravity = 0.0098f;
	int health;
	float velocityY = 0;
	float velocityX = 0;
	vect2d centre;
	float length;
	float height;
	float radius;
	bool grounded = false;
	bool collision = false;
	bool isCollidingBelow = false;
	bool isCollidingAbove = false;
	bool isCollidingLeft = false;
	bool isCollidingRight = false;

public:	

	const float PI = 3.1415926535897932384626433832795f;

	Object2D();
	
	Object2D(vect2d c, int heal,  float l, float h, float r, char * textureName);

	int getHealth();

	Object2D::collidingWith getMaterialCollidingWith();

	vect2d getCentre();

	float getVelocityX();

	float getVelocityY();

	float getLength();

	float getHeight();

	float getRadius();

	bool getCollision();

	bool getIsCollidingBelow();

	bool getIsCollidingAbove();

	bool getIsCollidingLeft();

	bool getIsCollidingRight();

	void SetMaterialCollidingWith(collidingWith materialCollidingWith);

	void setHealth(int h);

	void setVelocityY(float vY);

	void setVelocityX(float vX);

	void setCentre(vect2d c);

	void setLength(float l);

	void setHeight(float h);

	void setCollision(bool collision);

	void setIsCollidingBelow(bool isCollidingBelow);

	void setIsCollidingAbove(bool isC);

	void setIsCollidingLeft(bool isCollidingLeft);

	void setIsCollidingRight(bool isCollidingRight);

	void setInertia(float inertia);

	//if object falls off screen - kill
	void fallCheck();

	virtual void groundCheck();

	void jump();

	void posUpdate();

	void draw(float r, float g, float b, vect2d player);

	GLuint loadPNG(char * name);

};

