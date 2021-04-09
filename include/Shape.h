#pragma once;

class Shape 
{
public:
	float rot_angle;
	Vec2d pos;

	virtual bool collide(Shape shape1, Shape shape2);
	virtual void draw();

};