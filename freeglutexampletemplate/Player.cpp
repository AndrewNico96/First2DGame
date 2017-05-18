#include "Player.h"
#include "projectile.h"
#include <vector>
#include <iostream>
#include "stdio.h"
#include "GL\freeglut.h"


Player::Player(){}


Player::Player(vect2d c, int heal, float l, float h, char * textureName) : Object2D(c, heal, l,  h, 0.0f, textureName){}


void Player::keyfunction(unsigned char key, int x, int y)
{
	//changes texture every 100ms for walking animation
	if (glutGet(GLUT_ELAPSED_TIME) - animationTimer > 100) {
		animationSwitcher++;
		animationTimer = glutGet(GLUT_ELAPSED_TIME);
	}
	std::cout << animationSwitcher;
	switch (key)
	{
	case 'a':
		if (animationSwitcher % 2 == 0)
			this->myTexture = walkingLeft1;
		else
			this->myTexture = walkingLeft2;
		if (materialCollidingWith == Object2D::collidingWith::DIRT || !grounded || materialCollidingWith == Object2D::collidingWith::MOVING) {
			velocityX = -0.9f;
		}
		if (materialCollidingWith == Object2D::collidingWith::ICE) {
			velocityX -= 0.15f;
			if (velocityX < -0.9f) {
				velocityX = -0.9f;
			}
		}
		if (materialCollidingWith == Object2D::collidingWith::SNOW)
			velocityX = -0.45f;
		break;
	case 'd':
		if (animationSwitcher % 2 == 0)
			this->myTexture = walkingRight1;
		else
			this->myTexture = walkingRight2;
		if (materialCollidingWith == Object2D::collidingWith::DIRT || !grounded || materialCollidingWith == Object2D::collidingWith::MOVING)
			velocityX = 0.9f;
		if (materialCollidingWith == Object2D::collidingWith::ICE) {
			velocityX += 0.15f;
			if (velocityX > 0.9f)
				velocityX = 0.9f;
		}
		if (materialCollidingWith == Object2D::collidingWith::SNOW)
			velocityX = 0.45f;
		break;
	case 'w':
		this->myTexture = standing;
		jump();
		jump();
		break;
	}

	switch (key)
	{
	case 'A':
		if (animationSwitcher % 2 == 0)
			this->myTexture = walkingLeft1;
		else
			this->myTexture = walkingLeft2;
		if (materialCollidingWith == Object2D::collidingWith::DIRT || !grounded || materialCollidingWith == Object2D::collidingWith::MOVING)
			velocityX = -0.9f;
		if (materialCollidingWith == Object2D::collidingWith::ICE) {
			velocityX -= 0.15f;
			if (velocityX > 0.9f)
				velocityX = 0.9f;
		}
		if (materialCollidingWith == Object2D::collidingWith::SNOW)
			velocityX = -0.45f;
		break;
	case 'D':
		if (animationSwitcher % 2 == 0)
			this->myTexture = walkingRight1;
		else
			this->myTexture = walkingRight2;
		if (materialCollidingWith == Object2D::collidingWith::DIRT || !grounded || materialCollidingWith == Object2D::collidingWith::MOVING)
			velocityX = 0.9f;
		if (materialCollidingWith == Object2D::collidingWith::ICE) {
			velocityX += 0.15f;
			if (velocityX > 0.9f)
				velocityX = 0.9f;
		}
		if (materialCollidingWith == Object2D::collidingWith::SNOW)
			velocityX = 0.45f;
		break;
	case 'W':
		jump();
		jump();
		break;
	}
}

void Player::keyfunctionReleased(unsigned char key, int x, int y)
{
	this->myTexture = standing;
	if (materialCollidingWith == Object2D::collidingWith::DIRT || materialCollidingWith == Object2D::collidingWith::SNOW || materialCollidingWith == Object2D::collidingWith::MOVING)
		velocityX = 0.0f;
}

void Player::attack(vect2d target, std::vector<projectile *>& projectiles)
{
	float duration = glutGet(GLUT_ELAPSED_TIME) - timer;
	if (duration >= 1000) {
		if (target.getX() < centre.getX()) {
			vect2d projectileCentre(centre.getX() - 30, centre.getY() + 20);
			projectiles.push_back(new projectile(projectileCentre, 100, target, 5, 25, 2.4f, " "));
		}
		if (target.getX() > centre.getX()) {
			vect2d projectileCentre(centre.getX() + 30, centre.getY() + 10);
			projectiles.push_back(new projectile(projectileCentre, 100, target, 5, 25, 2.4f, " "));
		}
		if (target.getX() == centre.getX()) {
			vect2d projectileCentre(centre.getX(), centre.getY() + 30);
			projectiles.push_back(new projectile(projectileCentre, 100, target, 5, 25, 2.4f, " "));
		}
		timer = glutGet(GLUT_ELAPSED_TIME);
	}
	count++;
	if (count > 150)
		count = 0;
}

void Player::draw(float r, float g, float b, vect2d humanPlayer) {

	//do not render offscreen objects
	if (abs(humanPlayer.getX() - centre.getX()) < 2000 &&
		abs(humanPlayer.getY() - centre.getY()) < 2000) {
		if (health > 0)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glGenTextures(1, &myTexture);
			glBindTexture(GL_TEXTURE_2D, myTexture);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_POLYGON);
			glColor3f(1.0, 1.0, 1.0);
			glTexCoord2f(0.0, 0.0); glVertex2f(((centre.getX()) - length), ((centre.getY()) - height));
			glTexCoord2f(0.0, 1.0); glVertex2f(((centre.getX()) - length), ((centre.getY()) + height));
			glTexCoord2f(1.0, 1.0); glVertex2f(((centre.getX()) + length), ((centre.getY()) + height));
			glTexCoord2f(1.0, 0.0); glVertex2f(((centre.getX()) + length), ((centre.getY()) - height));
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
	}
	
}

GLuint Player::loadPNG(char * name)
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


