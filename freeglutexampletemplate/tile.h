#pragma once
#include "Object2D.h"
#include "Platform.h"
#include "BoundBox.h"
#include <vector>
class tile : public Object2D
{
public:

	enum material { DIRT, SNOW, ICE };

private:
	vect2d centre;
	int length;
	material mat;
	std::vector<Platform *> platformTiles;

public:
	tile();
	
	tile(vect2d centre, int length, material mat);
	
	void createTileArray();

	void draw(float r, float g, float b, vect2d player);

	void collision(Object2D * collider);

	void projectileHitTile(projectile * pro);

	void clearCollisions();

	~tile();
};

