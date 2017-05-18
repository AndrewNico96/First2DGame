#include "GameOver.h"



GameOver::GameOver()
{
}

void GameOver::loop()
{
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glLoadIdentity();
	menu->draw();

	glutSwapBuffers();
}


GameOver::~GameOver()
{
}
