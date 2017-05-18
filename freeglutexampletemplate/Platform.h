#include "vect2d.h"
#include "Object2D.h"
#pragma once

class Platform : public Object2D
{
public: 
	enum material { DIRT, SNOW, ICE, MOVING};

private:

	material mat;

public:
	
	Platform();

	Platform(vect2d c, float l, float h, material m, char * textureName);

	material getMat();

	void groundCheck();

	//sets health depending on platform type
	void setStartingHealth();

	void posUpdate();


};

  