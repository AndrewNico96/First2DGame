
//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle
#include "Image_Loading\glew.h"
#include "Object2D.h"
#include <math.h>
#include "platform.h"
#include "Player.h"
#include "projectile.h"
#include "BoundBox.h"
#include "tile.h"
#include "level1.h"
#include "level2.h"
#include <stdio.h>
#include <iostream>
#include "GL\freeglut.h"
#include "globals.h"
#include "Menu.h"
#include "GameOver.h"
#include "Win.h"


enum stages { MENU, L1, L2, GAME_OVER, WIN };
level1 * l1;// = new level1();
level2 * l2;// = new level2();
Menu * menu;
GameOver * gameOver;
Win * winner;




stages thisStage = MENU;
int	mouse_x = 0, mouse_y = 0;
bool LeftPressed = false;
int screenWidth = 1680, screenHeight = 1050;
bool keys[256];
float timeStart = 0.0f;
float timeEnd;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyfunction(unsigned char key, int x, int y);
void keyfunctionReleased(unsigned char key, int x, int y);
void special(int key, int x, int y);
void update();				//called in winmain to update variables
void setFPS(int fps);
void timer(int);

/*************    START OF OPENGL FUNCTIONS   ****************/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	l1->getBG()->draw();
	l2->getBG()->draw();
	
	//mouse cursor
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 1.0f);
		glVertex2f(mouse_x - 5, mouse_y - 5);
		glVertex2f(mouse_x - 5, mouse_y);
		glVertex2f(mouse_x, mouse_y);
		glVertex2f(mouse_x, mouse_y - 5);
	glEnd();
	if (thisStage == GAME_OVER)
		gameOver->loop();
	if (thisStage == MENU){
		if (LeftPressed) {
			thisStage = L1;
		}
		else
			menu->loop();
	}
	if (thisStage == L1) {
		if (l1->getToken()->getCollision()) {
			thisStage = L2;
		}
		else {
			l1->loop();
			if (LeftPressed)
				l1->shoot(mouse_x, mouse_y);
		}
		if (l1->getPlayer()->getHealth() <= 0)
			thisStage = GAME_OVER;
	}
	if (thisStage == L2) {
		if (l2->getToken()->getCollision()) {
			thisStage = WIN;
		}
		else{
			l2->loop(); 
			if (LeftPressed)
				l2->shoot(mouse_x, mouse_y);
		}
		if (l2->getPlayer()->getHealth() <= 0)
			thisStage = GAME_OVER;
	}
	if (thisStage == WIN) {
		winner->loop();
	}
	timeEnd = glutGet(GLUT_ELAPSED_TIME);
	deltaT = timeEnd - timeStart;
	timeStart = timeEnd;
}

static int redisplay_interval;

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(redisplay_interval, timer, 0);
}

void setFPS(int fps)
{
	redisplay_interval = 1000 / fps;
	glutTimerFunc(redisplay_interval, timer, 0);
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; screenHeight = height;           // to ensure the mouse coordinates match 
														  // we will use these values to set the coordinate system

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();

	gluOrtho2D(0, width, 0, height);		// set the coordinate system for the window
											//glTranslatef(pl->getCentre().getX(), pl->getCentre().getY(), 0.0f);




	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
														//glOrtho(pl.getCentre().getX()- 50.0f, pl.getCentre().getX() - 25.0f, 0.0f, 0.0f, -1.0f, 1.0f);
	glLoadIdentity();
	//glOrtho(pl.getCentre().getX()- 50.0f, pl.getCentre().getX() - 25.0f, 0.0f, 0.0f, -1.0f, 1.0f);
	//glTranslatef(pl.getCentre().getX(), pl.getCentre().getY(), 0.0f);

}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);						//sets the clear colour to yellow
	menu = new Menu();
	l1 = new level1();
	l2 = new level2();
	gameOver = new GameOver();
	winner = new Win();								//glClear(GL_COLOR_BUFFER_BIT) in the display function
															//will clear the buffer to this colour.
}

void keyfunction(unsigned char key, int x, int y)
{
	if (thisStage == L1)
		l1->getPlayer()->keyfunction(key, x, y);
	if (thisStage == L2)
		l2->getPlayer()->keyfunction(key, x, y);	
}

void keyfunctionReleased(unsigned char key, int x, int y)
{
	if(thisStage == L1)
		l1->getPlayer()->keyfunctionReleased(key, x, y);
	if(thisStage == L2)
		l2->getPlayer()->keyfunctionReleased(key, x, y);
}


void special(int key, int x, int y){}

void mouseMotion(int x, int y)
{
	mouse_y = screenHeight - y;
	mouse_x = x;
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			LeftPressed = true;
		}
		else
			LeftPressed = false;
		break;
	case GLUT_RIGHT_BUTTON:

		break;
	default:
		break;
	}
}

void update()
{

	glutPostRedisplay();
}
/**************** END OPENGL FUNCTIONS *************************/
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("OpenGL FreeGLUT Template");
	glutSetCursor(GLUT_CURSOR_NONE);
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMotion);
	glutIdleFunc(update);
	setFPS(60);


	glutKeyboardFunc(keyfunction);
	glutKeyboardUpFunc(keyfunctionReleased);
	//pl->setVelocityX(0.0f); 

	//glutSpecialFunc(special);

	glutMainLoop();

	return 0;

}


