#pragma once
#include "ParticleLink.h"
class Rod : public ParticleLink
{
public:
	float length = 1;
	float restitution = 0;

	ParticleContact* getContact() override;
};

