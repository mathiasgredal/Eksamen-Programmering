#pragma once

#include <vector>

class Scene 
{
public:
	Scene(std::vector <Entity> _entities);

private:
	std::vector <Entity> entities = {};
	//hvad g�r vi med vec2d = lave egen
	vec2d gravity_k;
	
	void step(float deltaT);
	

};