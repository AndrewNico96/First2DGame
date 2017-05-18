#include "level1.h"



level1::level1()
{

	//populate tiles vector
	tiles.push_back(new tile(v, 200, tile::DIRT));
	tiles.push_back(new tile(v2, 50, tile::DIRT));
	tiles.push_back(new tile(v3, 5, tile::SNOW));
	tiles.push_back(new tile(v4, 10, tile::ICE));
	tiles.push_back(new tile(v5, 50, tile::DIRT));
	tiles.push_back(new tile(v6, 10, tile::SNOW));
	tiles.push_back(new tile(v7, 10, tile::DIRT));
	tiles.push_back(new tile(v9, 10, tile::DIRT));
	tiles.push_back(new tile(v10, 50, tile::ICE));

}


level1::~level1(){}

void level1::loop()
{
	// set the coordinate system for the window
	gluOrtho2D(0, screenWidth, 0, screenHeight);		

	glLoadIdentity();
	glTranslatef( 1.0f, screenHeight/2 / 4, 0.5f);
	if (pl->getCentre().getX() > screenWidth + 300)
		glTranslatef(-pl->getCentre().getX() + screenWidth + 300, 0, 0.5f);
	if (pl->getCentre().getX() < 300)
		glTranslatef(-pl->getCentre().getX() + 300, 0, 0.5f);

	//check if player has fallen offscreen
	pl->fallCheck();

	//check if player has been caught by the npc.
	if (b.genericCollision(anNpc, pl)) {
		if(anNpc->getHealth() > 0)
			pl->setHealth(0);
	}

	//movement controllers
	anNpc->ai(pl->getCentre());
	p->move();
	navi->follow(pl->getCentre());

	//collision detections
	//check collision between token and player
	b.genericCollision(pl, token);
	
	//check collision between moving platform and player
	//distance culling
	if (abs(p->getCentre().getX() - pl->getCentre().getX()) < 50 &&
		abs(p->getCentre().getY() - pl->getCentre().getY()) < 50) {
		b.platformCollision(p, pl);
	}
	
	//check collision between npc and moving platform
	//distance culling
	if (abs(p->getCentre().getX() - pl->getCentre().getX()) < 50 &&
		abs(p->getCentre().getY() - pl->getCentre().getY()) < 50) {
		b.platformCollision(p, anNpc);
	}

	//check projectiles vs vulnerable objects
	for (std::vector<projectile *>::iterator i = projectiles.begin(); i != projectiles.end(); ++i) {
		projectile* pro = *i;
		b.projectileHit(pro, pl);
		b.projectileHit(pro, anNpc);
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
		t->collision(anNpc);
	}


	//Positional Update Methods
	//projectile updates
	for (std::vector<projectile *>::iterator i = projectiles.begin(); i != projectiles.end(); ++i) {
		projectile* pro = *i;
		pro->posUpdate();
	}

	//update positions of non-static objects
	pl->posUpdate();
	p->posUpdate();
	anNpc->posUpdate();
	navi->posUpdate();

	//draw arrows
	arrow1->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	arrow2->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	arrow3->draw(1.0f, 1.0f, 1.0f, pl->getCentre());

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
	p->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	anNpc->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	navi->draw(1.0f, 1.0f, 1.0f, pl->getCentre());


	//draw projectiles
	for (std::vector<projectile *>::iterator i = projectiles.begin(); i != projectiles.end(); ++i) {
		projectile* pro = *i;
		pro->draw(1.0f, 1.0f, 1.0f, pl->getCentre());
	}

	waterForeGround->draw();

	//reset collision data to be recalculated next frame
	pl->setCollision(false);
	p->setCollision(false);
	anNpc->setCollision(false);

	for (std::vector<tile *>::iterator i = tiles.begin(); i != tiles.end(); ++i) {
		tile* t = *i;
		t->clearCollisions();
	}

	glutSwapBuffers();
}

Object2D * level1::getToken()
{
	return token;
}

BackGround * level1::getBG()
{
	return BG;
}

Player *level1::getPlayer()
{
	return pl;
}

void level1::shoot(float x, float y){
	vect2d mouse(x , y);
	pl->attack(mouse, projectiles);
}



