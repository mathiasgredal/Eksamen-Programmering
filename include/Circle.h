#pragma once

#include "Shape.h"

class Circle : Shape {
public:
	Circle(r, Vec2d pos)
	float r;
	float rot_angle;

	void draw() override;
	void collide(Shape shape1, Shape shape2) override;




private:
	
};