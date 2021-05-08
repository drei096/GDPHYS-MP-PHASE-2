#include "Cable.h"
#include <iostream>

ParticleContact* Cable::getContact()
{
	//float curr_len = getDistance();

	std::cout << "anchor point: " << anchorPoint.x << "," << anchorPoint.y << std::endl;

	float curr_len = (anchorPoint - particles[0]->position).magnitude();

	if (curr_len == length)
		return nullptr;


	ParticleContact* ret = new ParticleContact();
	ret->particles[0] = particles[0];
	ret->particles[1] = NULL;

	PhysVector dir = anchorPoint - particles[0]->position;  //(245,80) is manually set anchor
	dir.normalize();

	std::cout << "curr length of cable: " << curr_len << std::endl;

	
	if (curr_len > length)
	{
		std::cout << "mahaba na" << std::endl;
		ret->collisonNormal = dir * -1;
		//ret->depth = curr_len - length;
	}
	else if (curr_len < length)
	{
		ret->collisonNormal = dir;
		//ret->depth = length - curr_len;
	}
	
	ret->restitution = restitution;

	return ret;

}

