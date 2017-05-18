#include "Win.h"



Win::Win()
{
}

void Win::loop()
{
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glLoadIdentity();
	menu->draw();

	glutSwapBuffers();
}

Win::~Win()
{
}
