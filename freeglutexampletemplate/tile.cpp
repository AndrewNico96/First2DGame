#include "tile.h"



tile::tile()
{
}

tile::tile(vect2d centre, int length, material mat)
{
	this->length = length;
	this->mat = mat;
	this->centre = centre;
	createTileArray();
}


void tile::createTileArray()
{
	for(int i=0; i<length; i++){
		vect2d v = vect2d(centre.getX() + i * 20, centre.getY());
		Platform * p = new Platform(v, 10, 10, (Platform::material)mat, "sky.png");
			if (mat == DIRT)
				p = new Platform(v, 10, 10, (Platform::material)mat, "WinterTileset/Tiles/5.png");
			if (mat == SNOW)
				p = new Platform(v, 10, 10, (Platform::material)mat, "WinterTileset/Tiles/2.png");
			if (mat == ICE)
				p = new Platform(v, 10, 10, (Platform::material)mat, "WinterTileset/Object/IceBox.png");
			platformTiles.push_back(p);
	}
}

void tile::draw(float r, float g, float b, vect2d player) {
	int count = 1;
	for (std::vector<Platform *>::iterator i = platformTiles.begin(); i != platformTiles.end(); ++i) {
		Platform * p = *i;
		p->draw(1.0, 1.0, 1.0, player);
	}
}

void tile::collision(Object2D * collider) {
	BoundBox b = BoundBox();
	for (std::vector<Platform *>::iterator i = platformTiles.begin(); i != platformTiles.end(); ++i) {
		Platform * p = *i;
		//health check
		//distance culling
		if(p->getHealth() > 0 && collider->getHealth() > 0 &&
			abs(p->getCentre().getX() - collider->getCentre().getX()) < 50 &&
			abs(p->getCentre().getY() - collider->getCentre().getY()) < 50)
			b.platformCollision(p, collider);
	}
}

//culling is taken care of in projectileHit method
void tile::projectileHitTile(projectile* pro) {
	BoundBox b = BoundBox();
	for (std::vector<Platform *>::iterator i = platformTiles.begin(); i != platformTiles.end(); ++i) {
		Platform * p = *i;
		b.projectileHit(pro, p);
	}
}

void tile::clearCollisions(){
	for (std::vector<Platform *>::iterator i = platformTiles.begin(); i != platformTiles.end(); ++i) {
		Platform * p = *i;
		p->setCollision(false);
	}
}

tile::~tile()
{
}
