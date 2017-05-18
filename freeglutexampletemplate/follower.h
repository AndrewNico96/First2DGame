#pragma once
#include "npc.h"

class follower : public npc
{
private:
	const float speed = 0.50f;

public:
	follower();
	follower(vect2d centre);
	void follow(vect2d player);
	void posUpdate();
	~follower();
};

