#include "level2.h"



level2::level2()
{

	//populate tiles vector
	tiles.push_back(new tile(v, 200, tile::ICE));
	tiles.push_back(new tile(v2, 50, tile::ICE));
	tiles.push_back(new tile(v3, 25, tile::ICE));
	tiles.push_back(new tile(v4, 20, tile::ICE));
	tiles.push_back(new tile(v5, 50, tile::ICE));
	tiles.push_back(new tile(v6, 25, tile::ICE));
	tiles.push_back(new tile(v7, 30, tile::ICE));
	tiles.push_back(new tile(v9, 28, tile::ICE));
	tiles.push_back(new tile(v10, 50, tile::ICE));

}


level2::~level2() {}

void level2::loop()
{
	// set the coordinate system for the window
	gluOrtho2D(0, screenWidth, 0, screenHeight);

	glLoadIdentity();
	//glScalef(2, 2, 1);
	
	glTranslatef(1.0f, screenHeight / 2 / 4, 0.5f);
	if (pl->getCentre().getX() > screenWidth + 300)
		glTranslatef(-pl->getCentre().getX() + screenWidth + 300, 0, 0.5f);
	if (pl->getCentre().getX() < 300)
		glTranslatef(-pl->getCentre().getX() + 300, 0, 0.5f);

	//check if player has fallen offscreen
	pl->fallCheck();

	navi->follow(pl->getCentre());

	//collision detections
	//check collision between token and player
	b.genericCollision(pl, token);

	//check projectiles vs vulnerable objects
	for (std::vector<projectile *>::iterator i = projectiles.begin(); i != projectiles.end(); ++i) {
		projectile* pro = *i;
		b.projectileHit(pro, pl);
		//check all projectiles vs tiles
		for (std::vector<tile *>::iterator j = tiles.begin(); j != tiles.end(); ++j) {
			tile* t = *j;
			if (pro->getHealth()>0)
				t->projectileHitTile(pro);
		}
	}

	//check tiles vs players
	for (std::vector<tile *>::iterator i = tiles.begin(); i != tiles.end(); ++i) {
		tile* t = *i;
		t->collision(pl);
	}


	//Positional Update Methods
	//projectile updates
	for (std::vector<projectile *>::iterator i = projectiles.begin(); i != projectiles.end(); ++i) {
		projectile* pro = *i;
		pro->posUpdate();
	}

	//update positions of non-static objects
	pl->posUpdate();
	navi->posUpdate();

	//draw platforms
	for (std::vector<tile *>::iterator i = tiles.begin(); i != tiles.end(); ++i) {
		tile* t = *i;
		t->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	}

	//draw objects 
	//if more non static objects were in the level
	//they could be stored in a vector and be called
	//from loop 
	pl->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	token->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	navi->draw(1.0f, 1.0f, 1.0f, pl->getCentre());

	//draw projectiles
	for (std::vector<projectile *>::iterator i = projectiles.begin(); i != projectiles.end(); ++i) {
		projectile* pro = *i;
		pro->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	}

	waterForeGround->draw();

	//reset collision data to be recalculated next frame
	pl->setCollision(false);

	for (std::vector<tile *>::iterator i = tiles.begin(); i != tiles.end(); ++i) {
		tile* t = *i;
		t->clearCollisions();
	}

	glutSwapBuffers();
}

Object2D * level2::getToken()
{
	return token;
}

BackGround * level2::getBG()
{
	return BG;
}

Player *level2::getPlayer()
{
	return pl;
}

void level2::shoot(float x, float y) {
	vect2d mouse(x, y);
	pl->attack(mouse, projectiles);
}



