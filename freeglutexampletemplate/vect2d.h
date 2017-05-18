#pragma once
class vect2d
{
private:
	
	float X;
	float Y;


public:

	vect2d::vect2d();
	vect2d::vect2d(float x, float y);
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();

	~vect2d();

};

