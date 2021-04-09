#pragma once

#include "Vec2d.h"

class Entity
{
public:
	Entity(Shape _shape);

	Shape shape; 
	Vec2d velocity;
	float ang_mom;
	float torque;
	float mass;
	float fric_coef;
	bool immovable;
	bool ghost;



private:


};