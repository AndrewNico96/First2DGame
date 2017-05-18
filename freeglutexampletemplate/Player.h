#pragma once
class Platform;
#include "vect2d.h"
#include "Object2D.h"
#include "projectile.h"
#include "Platform.h"


class Player : public Object2D //create object2d class - parent class of platform, player, projectile etc
{
protected:
	int animationSwitcher = 0;
private:

	GLuint standing = loadPNG("character/alienBlue_stand.png");
	GLuint walkingLeft1 = loadPNG("character/alienBlue_walk3.png");
	GLuint walkingLeft2 = loadPNG("character/alienBlue_walk4.png");
	GLuint walkingRight1 = loadPNG("character/alienBlue_walk1.png");
	GLuint walkingRight2 = loadPNG("character/alienBlue_walk2.png");
	float timer = 0;
	float animationTimer = 0;



	
public:
	int count = 0;
	Player();

	Player(vect2d c, int heal, float l, float h, char * textureName);


	void keyfunction(unsigned char key, int x, int y);

	void keyfunctionReleased(unsigned char key, int x, int y);

	void attack(vect2d target, std::vector<projectile*>& projectiles);

	void draw(float r, float g, float b, vect2d humanPlayer);

	GLuint loadPNG(char * name);


};


