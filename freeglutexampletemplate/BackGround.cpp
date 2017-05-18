#include "BackGround.h"



BackGround::BackGround(){}

BackGround::BackGround(vect2d centre, char * textureName, float scroller, float length, float height):Object2D(centre, 100, length, height, 0.0f, textureName){
	this->scroller = scroller;
}

void BackGround::draw()
{


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, myTexture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0 + X, 0.0); glVertex2f(((centre.getX()) - length), ((centre.getY()) - height));
	glTexCoord2f(0.0 + X, 20.0); glVertex2f(((centre.getX()) - length), ((centre.getY()) + height));
	glTexCoord2f(20.0 + X, 20.0); glVertex2f(((centre.getX()) + length), ((centre.getY()) + height));
	glTexCoord2f(20.0 + X, 0.0); glVertex2f(((centre.getX()) + length), ((centre.getY()) - height));
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	X += scroller;

}



BackGround::~BackGround(){}
