#pragma once
#include "ParticleLink.h"
class Cable : public ParticleLink
{
public:
	float length;
	float restitution = 0;
	PhysVector anchorPoint = PhysVector(0,0);
	
	ParticleContact* getContact() override;
};

