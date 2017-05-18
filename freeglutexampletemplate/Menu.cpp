#include "Menu.h"



Menu::Menu()
{
}

void Menu::loop() {
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glLoadIdentity();
	menu->draw();

	glutSwapBuffers();
}

Menu::~Menu()
{
}
