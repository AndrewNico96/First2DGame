#include "Object2D.h"
#include <math.h>
#include <stdio.h>
#include <iostream>


Object2D::Object2D()
{

}


Object2D::Object2D(vect2d c, int heal, float l, float h, float r, char * textureName)
{
	this->centre = c;
	this->health = heal;
	this->length = l;
	this->height = h;
	this->radius = r;
	this->myTexture = loadPNG(textureName);

}


/**************************ACCESSORS*****************************/
int Object2D::getHealth(){
	return health;
}

vect2d Object2D::getCentre(){
	return centre;
}

float Object2D::getLength() {
	return length;
}

float Object2D::getHeight() {
	return height;
}

float Object2D::getVelocityX() {
	return velocityX;
}

float Object2D::getVelocityY() {
	return velocityY;
}

Object2D::collidingWith Object2D::getMaterialCollidingWith(){
	return materialCollidingWith;
}

float Object2D::getRadius(){
	return radius;
}

bool Object2D::getCollision() {
	return collision;
}

bool Object2D::getIsCollidingBelow() {
	return isCollidingBelow;
}

bool Object2D::getIsCollidingLeft()
{
	return isCollidingLeft;
}

bool Object2D::getIsCollidingRight()
{
	return isCollidingRight;
}

/**************************MUTATORS*****************************/
void Object2D::SetMaterialCollidingWith(collidingWith materialCollidingWith)
{
	this->materialCollidingWith = materialCollidingWith;
}

void Object2D::setHealth(int h) {
	this->health = h;
}

void Object2D::setVelocityY(float vY) {
	this->velocityY = vY;
}

void Object2D::setVelocityX(float vX) {
	this->velocityX = vX;
}

void Object2D::setCentre(vect2d c) {
	this->centre = c;
}

void Object2D::setLength(float l) {
	this->length = l;
}
void Object2D::setHeight(float h) {
	this->height = h;
}

void Object2D::setCollision(bool collision)
{
	this->collision = collision;
}

void Object2D::setIsCollidingBelow(bool isC) {
	this->isCollidingBelow = isC;
}

bool Object2D::getIsCollidingAbove() {
	return isCollidingAbove;
}


void Object2D::setIsCollidingAbove(bool isC) {
	this->isCollidingAbove = isC;
}


void Object2D::setIsCollidingLeft(bool isCollidingLeft){
	this->isCollidingLeft = isCollidingLeft;
}

void Object2D::setIsCollidingRight(bool isCollidingRight){
	this->isCollidingRight = isCollidingRight;
}

void Object2D::setInertia(float inertia){
	this->inertia = inertia;
}

/**************************PHYSICS FUNCTIONS*****************************/
void Object2D::fallCheck() {
	if (centre.getY() < -25)
		health = 0;
}

void Object2D::groundCheck()
{
	if (isCollidingBelow) {
		grounded = true;
	}
	else
		grounded = false;

}

void Object2D::jump() {
	//different jump velocity based on material type of platform
	if (grounded) {
		centre.setY(centre.getY() + 1);
		if(materialCollidingWith == Object2D::collidingWith::DIRT)
			velocityY = 1.5f;
		if (materialCollidingWith == Object2D::collidingWith::SNOW)
			velocityY = 1.0f;
		if (materialCollidingWith == Object2D::collidingWith::ICE)
			velocityY = 1.375;
		if (materialCollidingWith == Object2D::collidingWith::MOVING)
			velocityY = 1.5f;
	}
}

void Object2D::posUpdate() {
	//don't update for dead objects
	if (health > 0) {
		//inertia calculations for moving platforms
		if (materialCollidingWith == collidingWith::MOVING)
			centre.setX(centre.getX() + ((velocityX + inertia) * deltaT)/5);
		else
			centre.setX(centre.getX() + (velocityX * deltaT)/5);
		centre.setY(centre.getY() + velocityY );
		//check if grounded before velocity adjustments
		groundCheck();
		if (!grounded) {
			if (isCollidingAbove) {
				//allow object to drop after hitting it's "head"
				centre.setY(centre.getY() - 1);
				velocityY = 0;
			}
			//decrement velocity by gravity
			velocityY -= gravity;
		}
		else
			velocityY = 0;
		//side collision considered when bottom and top collision not currently active
		if (isCollidingLeft && !isCollidingBelow && !isCollidingAbove ||
			isCollidingRight && !isCollidingBelow && !isCollidingAbove) {
			//bounce off
			velocityX = -velocityX;
		}
		groundCheck();
	}
}

/**************************OPENGL FUNCTIONS*****************************/
void Object2D::draw(float r, float g, float b, vect2d player) {
	
	//do not render offscreen objects
	if (abs(player.getX() - centre.getX()) < 2000 &&
		abs(player.getY() - centre.getY()) < 2000) {
		//check if is a circle (has a radius)
		if (radius == 0.0f && health > 0)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, myTexture);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_POLYGON);
			glColor3f(r, g, b);
			glTexCoord2f(0.0, 0.0); glVertex2f(((centre.getX()) - length), ((centre.getY()) - height));
			glTexCoord2f(0.0, 1.0); glVertex2f(((centre.getX()) - length), ((centre.getY()) + height));
			glTexCoord2f(1.0, 1.0); glVertex2f(((centre.getX()) + length), ((centre.getY()) + height));
			glTexCoord2f(1.0, 0.0); glVertex2f(((centre.getX()) + length), ((centre.getY()) - height));
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
		else if (health > 0)
		{
			glBegin(GL_POLYGON);
			for (float i = 0; i < 360; i++)
			{
				float xcoord = centre.getX() + radius * cosf(i*(PI / 180.0f));
				float ycoord = centre.getY() + radius * sinf(i*(PI / 180.0f));
				glVertex2f(xcoord, ycoord);
			}
			glEnd();
		}
	}
}

GLuint Object2D::loadPNG(char * name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID = 0;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	return myTextureID;
}

